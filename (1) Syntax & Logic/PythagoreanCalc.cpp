#include <iostream>
#include <cmath>
#include <limits> 


void clean() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

double checkNum(double& number, int& missing) {                   // Checks if the number is a valid number or not               
    if (std::cin.fail() || number == 0) {                         // If the input was invalid or 0, it is considered as the missing variable
        std::cout << "Missing Variable Initialized" << std::endl;
        clean();

        missing++;                                                // Increments the missing counter when this condition is true
        return 0.0;                                               // We still have to return 0                 
                                                                  
    } else {
        number = std::abs(number);                                // Absolute Value, Turns any negatives into positives because
        return number;                                            // That ain't right for Pythagorean Triangles!
    }
}

double calculate(double& hypo, double& s1, double& s2) {        // The Pythagorean Calculator
    double result{};

    if (hypo == 0) {                                            // Solving for the Hypotenuse
        result = std::sqrt((pow(s1, 2))+(pow(s2, 2)));

    } else {                                                    // Solving for a Side
        double knownSide = (s1 == 0 ) ? s2 : s1;                // Uses the side with a value as a substitute for the equation
        result = std::sqrt((pow(hypo, 2))-(pow(knownSide, 2))); 
    }

    return result;
}




int main () {
    double hypotenuse{0}, sideA{0}, sideB{0}, final{0};
    int missing {};
    bool hypoState{true}, invalidGeometry {false};

    std::cout << "              Pythagorean Calculator \n";
    std::cout << "================================================== \n";
    std::cout << "(Type 0 or a Nonnumerical to set a missing value)\n";
    std::cout << "   (Negative Inputs will turn into Positives)\n";
    std::cout << "================================================== \n";
    
    do {
        missing = 0;                        // A counter to check how many variables are missing
        invalidGeometry = false;            // Invalid Geometry checker cuz math stuff
        
        std::cout << "Hypotenuse: ";
        std::cin >> hypotenuse;
        hypotenuse = checkNum (hypotenuse, missing);

        hypoState = (hypotenuse > 0);     // This checks if hypotenuse is a missing value or not
                                          // For the final Output
        std::cout << "Side 1: ";
        std::cin >> sideA;
        sideA = checkNum (sideA, missing);

        std::cout << "Side 2: ";
        std::cin >> sideB;
        sideB = checkNum (sideB, missing);


        if (missing >= 2) {
            std::cout << "Error: Need at least 2 numbers to solve!\n";

        } else if (missing == 0) {
            std::cout << "Error: Can't solve if there's already 3 numbers!\n";

        } else if (hypotenuse > 0) {                                                    
            if (hypotenuse <= sideA || hypotenuse <= sideB) {
                std::cout << "Error: Hypotenuse must be the longest side!\n";
                invalidGeometry = true;
            }
        }
    } while (missing >= 2 || missing == 0 || invalidGeometry); // This keeps looping until there's only 2 known variables, and said variables make up a valid right triangle

    final = calculate(hypotenuse, sideA, sideB);                // CALCULATIN MATH!

    std::cout << "================================================== \n";
    if (hypoState == false) {
        std::cout << "Missing Hypotenuse = " << final;

    } else {
        std::cout << "Missing Side = " << final;
    }

    std::cout << "\n==================================================" << std::endl;

    return 0;
}