// ============================================================
//  EXPENSE TRACKER
// ============================================================
// If you read my last update for this exercise.
// sorry about that one. I finished it now :D
//
// I gave up on the fancy text-wrapping-for-long-item-names
// thing. setw() from <iomanip> is good enough for now.
// ============================================================

#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <iomanip>
#include <string_view>

// Menu options, but as actual words instead of magic numbers.
enum class Mode {
    ADD,
    EDIT,
    DELETE,
    EXIT,
};


// Used a struct instead of a class because there's no behavior to
// hide here, just data sitting around being data. 
// Classes are for when things need privacy and rules.
// the name "Items" should've been "Item" but eh... too late for that.
struct Items {
    std::string name {};
    double cost {};
};

// THE generic input reader. This took me a genuinely embarrassing
// amount of time to get working, but it means I never have to
// hand-write the same shit over and over again. 
//
// Step by step, this thing:
//   1. Prints whatever prompt you give it.
//   2. Reads a value of type T.
//   3. Runs it through your validator (usually a lambda) to see
//      if it's actually acceptable, not just "technically a number."
//   4. If it fails either of those checks, it cleans up cin's mess
//      and makes the user try again instead of looping forever
//      printing the same prompt at lightspeed (RIP my terminal,
//      day one of figuring out cin.fail() existed).
//
// 'T' is whatever type you're reading (int, double, etc).
// 'Validator' is a lambda that decides if the value counts as valid.
template <typename T, typename Validator>
T readValue(std::string_view prompt, Validator valid,
            std::string_view error = "Invalid Input \n") {
    T value {};

    while (true) {
        std::cout << prompt << std::flush;

        // Only escape the loop if BOTH the extraction succeeded
        // AND the validator gives it a thumbs up. Either one failing
        // sends you right back to "try again."
        if (std::cin >> value && valid(value)) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        // Input failed -> cin is now sulking in a fail state and
        // refusing to read anything else. Clear it and throw away
        // whatever garbage was actually typed.
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << error;
    }
}

// Separate function just for reading full lines of text, because
// 'cin >>' and 'getline' do NOT play nice together and I learned
// that the hard way
std::string readLine(std::string_view prompt) {
    std::string text {};

    std::cout << prompt << std::flush;
    std::getline(std::cin, text);

    return text;
}

class Table {
private:
    // The actual list of expenses. Kept private so nothing outside
    // this class can reach in and mess with it directly - all
    // changes have to go through the class's own functions.
    std::vector<Items> content {};

    // Asks the user which item they want, with built-in protection
    // against off-by-one nonsense.
    //
    // Quick context for why this function even exists: humans count
    // starting at 1 ("item #1"), but vectors count starting at 0.
    // Forgetting this distinction is how programs crash on a perfectly
    // reasonable-looking input. So: the menu shows numbers starting
    // at 1, and this function quietly subtracts 1 before handing
    // back the real vector index. Everyone's happy, nobody crashes.
    int getValidIndex() {
        if (content.empty()) {
            std::cout << "No items to select.\n";
            return -1;
        }

        int index = readValue<int>(
            "Enter item number (0 to cancel): ",
            [this](int n) {                                                 // 'this' is captured so the lambda can peek at content.size().
                return n >= 0 && n <= static_cast<int>(content.size());     // Valid range: 0 (cancel) through however many items exist.
            },

            "Choose a valid number.\n"
        );

        return index == 0 ? -1 : index - 1;          // 0 means "actually nevermind."
    }                                                 // -1 is my homemade signal for "nothing was actually selected."

public:
    void addItem() {
        Items newItem {                              // Build the new item straight from user input, no middleman.
            readLine("Enter item name: "),

            readValue<double>(
                "Enter cost: $",
                [](double cost) {
                    return cost >= 0;
                },
                "Enter a non-negative number.\n"
            )
        };

        content.push_back(newItem);                  // Tack it onto the end of the list.

        std::cout << "Expense added.\n";
    }

    void editItem() {
        int idx = getValidIndex();

        if (idx == -1) {                             // No items existed, or the user bailed with 0. Either way, nothing to edit.
            std::cout << "Edit cancelled.\n";
            return;
        }

        // Letting an empty Enter key cancel the edit so nobody
        // accidentally renames their "Rent" expense to "" because
        // they fat-fingered the Enter key.
        std::string newName = readLine("Enter new name (press Enter to cancel): ");

        if (newName.empty()) {
            std::cout << "Edit cancelled.\n";
            return;
        }

        // A reference here means 'item' IS the real entry inside
        // the vector, not some throwaway copy. Whatever I change
        // through 'item' actually changes the stored data.
        Items& item = content[idx];

        item.name = newName;

        item.cost = readValue<double>(
            "Enter cost: $",
            [](double cost) {
                return cost >= 0;
            },
            "Enter a non-negative number.\n"
        );

        std::cout << ">> Item updated.\n";
    }

    void deleteItem() {
        int idx = getValidIndex();

        // IMPORTANT, underlined, bolded, in my head: do NOT remove
        // this check. Without it, a cancelled selection (-1) sails
        // straight into content.begin() + (-1), which is the kind
        // of "The bug nobody invited" scenario.
        // Undefined behaviour type shit.
        if (idx == -1) {
            std::cout << ">> Delete cancelled.\n";
            return;
        }

        // erase() yeets the item at the chosen index out of the vector.
        content.erase(content.begin() + idx);

        std::cout << ">> Item removed.\n";
    }

    double getTotalCost() const {
        double total {};

        // Walk through every expense and add up the damage.
        // 'const Items&' so we're just looking, not copying and
        // definitely not editing - this function only reports
        // the total, it doesn't get to change anyone's data.
        for (const Items& item : content) {
            total += item.cost;
        }

        return total;
    }

    void displayTable() const {
        std::cout << "\n[ EXPENSE TRACKER ]\n"
                  << std::left << std::setw(6) << "No."      // 'left', 'right', and 'setw' all live in <iomanip>.
                  << std::setw(25) << "Expense"
                  << std::right << std::setw(12) << "Cost"
                  << "\n------------------------------------------------\n";

        if (content.empty()) {
            std::cout << "\nNO EXPENSES RECORDED...\n"
                      << "\n------------------------------------------------\n";
            return;
        }

        // size_t because vector::size() returns size_t, and the
        // compiler will absolutely give me a dirty look if I try
        // to compare it against a plain int.
        for (size_t i = 0; i < content.size(); ++i) {
            std::cout << std::left << std::setw(6) << i + 1
                      << std::setw(25) << content[i].name
                      << std::right << "$"
                      << std::fixed << std::setprecision(2)
                      << std::setw(11) << content[i].cost
                      << '\n';
        }

        std::cout << "\n------------------------------------------------\n"
                  << std::left << std::setw(31) << "Total :"
                  << std::right << "$"
                  << std::setw(11) << getTotalCost()
                  << '\n';
    }
};

int main() {
    Table expenses {};                                     // One Table to rule everything. CRAZY!

    // Main loop, and notably: a plain while(true), not a do-while.
    // do-while is for "do the thing, THEN check" situations.
    // while is for "as long as this condition holds" situations.
    // This is the second kind.
    while (true) {
        expenses.displayTable();                           // Show the current state...

        int choice = readValue<int>(                       // ...ask what to do next...
            "\n0. Add Expense\n"
            "1. Edit Expense\n"
            "2. Delete Expense\n"
            "3. Exit\n"
            "Enter your choice: ",

            [](int n) {                                     // Only 0 through 3 are allowed. Anything else gets rejected.
                return n >= 0 && n <= 3;
            },

            "Invalid Input.\n"
        );

        switch (static_cast<Mode>(choice)) {                // ...convert the raw number into a named Mode...
            case Mode::ADD:                                 // ...so the switch reads like English instead of a riddle.
                expenses.addItem();
                break;

            case Mode::EDIT:
                expenses.editItem();
                break;

            case Mode::DELETE:
                expenses.deleteItem();
                break;

            case Mode::EXIT:
                std::cout << "Bye Bye!\n";
                return 0;
        }
    }
}