#include <iostream>
#include <algorithm>
#include <cctype>

    //Relatively simple Palindrome Checker to see if the user's input is the same word when reversed

int main() 
{
    std::string input {}, reverseinput {};
    bool success {false};

    std::cout << "[Palindrome Checker]\n";
    std::cout << "Input to check : ";
    do {
        std::getline(std::cin, input);

        if (input.empty()) {                                                 // Skips the loop if the input is empty
            std::cout << "Input is empty! Try again: ";
            continue;
        }
                                                                             // Skips the loop if the input doesn't have alphabetical characters
        if (std::find_if(input.begin(), input.end(), [](char c) {return !std::isalpha(c);}) !=input.end()){
            std::cout << "Invalid! Try again: ";                             // Can also be used to refuse anything beyond a single word
            continue;                                                       
        }
        
        std::transform(input.begin(), input.end(), input.begin(),::tolower); // Normalizes the characters to lower case to properly check if both variables match

        reverseinput = std::string(input.rbegin(), input.rend());            // Reverses the positions of the initial characters

        if (reverseinput == input) {                                         // Compares the two variables to see if they both match
            input[0] = toupper(input[0]);                                    // This makes the first character uppercase for readability because we previously normalized it before
            std::cout << input << " is a Palindrome!" << std::endl;
        } else {
            input[0] = toupper(input[0]);
            std::cout << input << " is not a Palindrome!" << std::endl;
        }

        success = true;                                                      //The first two if statements prevent the program from concluding since it skips the entire loop, including 
    } while (success == false);                                              //the boolean assignment, So it keeps looping until the program completely runs through the code
}