#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <algorithm>

void clean() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Initially I wanted to use a vector to keep an array of numbers for the program to select with using the function below, but it wasn't necessary actually...
// I can just pop in the minimum and maximum values inside the uniform_int_distribution and it pretty much selects it from there

int chosenNumber (int &min, int &max) {
    static std::random_device rando;       // random seed
    static std::mt19937 engine(rando());   // Random engine with a random seed woah  
                                           // static ensures that it's only created once

    std::uniform_int_distribution<int> dist(min, max); // A random distribution range from min to max

    int randoNumbo = dist(engine);  // Selects a random number from the range using the randomizer
    
    return randoNumbo;
}



int main() {
    double inputMin{}, inputMax{};
    int inputAnsw{};

    std::cout << "Number Guessing Game\n";
    std::cout << "====================\n" ;
    std::cout << "(Whole Numbers Only)\n";
   
   do {
    std::cout << "Minimum Number: ";
    while (!(std::cin >> inputMin) || (inputMin - (int)inputMin) > 0) { // Loops if the input is not a whole number, 1st condition checks if the input is a double
        std::cout << "Invalid input! Try again: ";                      // 2nd condition checks if the difference of its own is greater than 0, meaning is this a number with decimals?
        clean();                                                        // I tried doing it with only !cin >> inputMin, but it printed the invalid output, truncated the number, still 
    }                                                                   // accepting the input and went to the other line, so I resorted to this

    std::cout << "Maximum Number: ";
    while (!(std::cin >> inputMax) || (inputMax - (int)inputMax) > 0) {
        std::cout << "Invalid input! Try again: ";
        clean();
    }

    if (inputMin > inputMax) {
        std::cout << "Minimum cannot be greater than Maximum!\n";
    }
    } while (inputMin > inputMax);
    

    int min = static_cast<int>(inputMin); // | variable = static_cast<int>(variable) | is more appropriate compared to just doing | int  variable = double variable 
    int max = static_cast<int>(inputMax); // Cuz compiler go wahhh wahahhh

    int finalNum =  chosenNumber(min, max);
    
    std::cout << "Guess what number I'm thinking between " << min << " and " << max << "!" << std::endl;
    std::cin >> inputAnsw;

    while (!(inputAnsw == finalNum)) {
        if (inputAnsw < finalNum) {
            std::cout << "Too low!\n";
            clean();
        }
            
        else if (inputAnsw > finalNum) {
            std::cout << "Too high!\n";
            clean();
        }

        std::cout << "Type a non-numerical number if you wanna give up hehe...\n";
        std::cin >> inputAnsw;

        if (std::cin.fail()) { //if the input is not an integer, it breaks the loop and concludes the program
            break;
        }
    }
    
    std::cout << "The correct answer is ";

    if (inputAnsw == finalNum) { // Differentiate between a solved and unsolved condition cuz I'm lazy and my brain is so foggy while writing this rn i should sleep...
        std::cout << "indeed ";
    } 

    std::cout << finalNum << "!" << std::endl;


    return 0;
}