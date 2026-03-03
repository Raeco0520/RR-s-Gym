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
    std::cout << "Expense Tracker";
    std::cout << "================";
    std::cout << "Item | Cost ";

    // Insert vectors here (item definition and item cost)
    // plan to make '=' and '|' to be dynamic depending on the length of the total characters within the row
    // kinda like python if they have it idk

    std::cout << "================";

}




int main () {
    std::vector<std::string> itemDefinition{};
    std::vector<double> itemCost{};
    int mode{};

    std::cout << "Choose Mode\n";
    std::cout << "0 - End Program\n";
    std::cout << "1 - Add Item\n";
    std::cout << "2 - Delete Item\n";
    std::cout << "3 - Edit Item\n";
    std::cout << "Selection: ";


    while (!(std::cin >> mode) || mode < 0 || mode > 3) {
        std::cout << "Invalid Input : ";
        clear();
        }

    switch (mode) {
        case 0 :

        case 1 :

        case 2 :

        case 3 :

        }

    return 0;
}