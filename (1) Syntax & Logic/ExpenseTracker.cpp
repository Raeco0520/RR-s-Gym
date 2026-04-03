#include <iostream>
#include <string>
#include <limits>
#include <vector>


//It's prolly just gonna be a more complex version of the To Do List

void clear() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void displayTable () {
    std::cout << "=================";
    std::cout << " Expense Tracker ";
    std::cout << "=================";
    std::cout << "  Item  |  Cost  ";

    // Insert vectors here (item definition and item cost)
    // plan to make '=' and '|' to be dynamic depending on the length of the total characters within the row
    // kinda like python if they have it idk

    std::cout << "=================";
}



struct Item{
    std::string name;
    double cost;
};  // Holy shit! My first struct or class thingy! Crazy!
    // The vectors were gonna have the same index anyways so might as well put in a struct 


int main () {
    std::vector<Item> items;
    int mode{};
    bool active{true};


    while (active) {
        std::cout << "Choose Mode\n";
        std::cout << "0 - End Program\n";
        std::cout << "1 - Add Item\n";
        std::cout << "2 - Delete Item\n";
        std::cout << "3 - Edit Item\n";

        while (!(std::cin >> mode) || mode < 0 || mode > 3) {
            std::cout << "Invalid Input: ";
            clear();
        }

        switch (mode) {

            /*
            
            Item is string type, use getline

            Cost is double type, make an edge case if its not a bool

            on the user's screen, the list goes 1 and above,
            but for indexes it starts from 0, to avoid confusion
            subtract from the user's input, and also add another edge 
            case same as cost.

            when deleting items, use vector.erase(vector.begin() + index)
            
            whopsie me been alot less frequent with my commits


            
            */

            case 1 :
            
            std::cout << "Item : ";

            std::cout << "Cost : ";
            break;

            case 2 :
            std::cout << "Index : ";

            break;

            case 3 :
            std::cout << "Index : ";
            std::cout << "Item : ";
            std::cout << "Cost : ";
            break;

            default :
            active = false;
            break;

        }

        displayTable();
    }

    return 0;
} 
// Apparently, the one I did was dumb. do-while for the entire program is not very readable, in this case I should use a while statement.
// Note to self, use do-while for action-then-check loops, use while for condition-driven loops.