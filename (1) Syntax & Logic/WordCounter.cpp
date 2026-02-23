#include <iostream>
#include <string>
#include <cctype> //for std::isspace to check whitespace
#include <algorithm> //for std::all_of for text validation


int main() {
    std::string userInput{};
    bool blank {true}, prev_WordState {false}; // Prev_WordState important for da word counter
    int count {};


    std::cout << "Word Counter\n";
    std::cout << "============\n";
    std::cout << "Type your text to start!" << std::endl;


    while (blank == true) {
        std::getline(std::cin, userInput);
        if (userInput.empty() || std::all_of(userInput.begin(),userInput.end(), [](char c) {return std::isspace(c);})) { // Loops if its empty or just whitespace
            std::cout << "Empty input! Try Again! ";
            blank = true;

        } else {
            blank = false;
        }
    }

    for (char text:userInput) {                                        // The Word Counter
        bool cur_WordState {false};

        if (std::isspace(text)) {
            cur_WordState = false;                                     // If the current iteration is whitespace, then it updates the current word state to false

        } else if (!(std::isspace(text)) && prev_WordState == false) { // A specific condition that increments the word counter if the current iteration is a char
            cur_WordState = true;                                      // and the previous state was a whitespace, meaning it's now in the beginning of a new word
            ++count;
        } else {
            cur_WordState = true;                                      // If its just a char and the previous char was a char, then its still part of a word so no new word
        }

        prev_WordState = cur_WordState;                                // Finally updates the prev_variable to the cur_variable's expression to prepare for the next iteration
    }

    std::cout << "I counted " << count << " words!";

    return 0;
}