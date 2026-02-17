#include <iostream>
#include <string>
#include <limits>
#include <unordered_map> //This is for the dictionary from Text to Morse and vice versa


using namespace std;

unordered_map<char, string> Dict = { //Text-to-Morse Map
    {'a', ".-"}, {'b', "-..."}, {'c', "-.-."}, {'d', "-.."}, {'e', "."},
    {'f', "..-."}, {'g', "--."}, {'h', "...."}, {'i', ".."}, {'j', ".---"}, 
    {'k', "-.-"}, {'l', ".-.."}, {'m', "--"}, {'n', "-."}, {'o', "---"}, 
    {'p', ".--."}, {'q', "--.-"}, {'r', ".-."}, {'s', "..."}, {'t', "-"}, 
    {'u', "..-"}, {'v', "...-"}, {'w', ".--"}, {'x', "-..-"}, {'y', "-.--"}, 
    {'z', "--.."}, // Alphabetical Characters
    
    {'1', ".----"}, {'2', "..---"}, {'3', "...--"}, {'4', "....-"}, {'5', "....."},
    {'6', "-...."}, {'7', "--..."}, {'8', "---.."}, {'9', "----."}, {'0', "-----"}, // Numerical Characters
    
    {',', "--..--"}, {'<', "-.---"}, {'.', ".-.-.-"}, {'>', "-.----"}, {'/', "-..-."},
    {'?', "..--.."}, {';', "-.-.-."}, {':', "---..."}, {'\'', ".----."}, {'\"', ".-..-."},
    {'[', ".--.."}, {'{', ".--.-"}, {']', ".--..-"}, {'}', ".--.--"}, {'\\', "-.-.-"}, 
    {'|', "--.-.-"}, {'`', "-..-.-"}, {'~', ".---.."}, {'!', "-.-.--"}, {'@', ".--.-."},
    {'#', "--.-."},  {'$', "...-.."}, {'%', "---.-"}, {'^', "......"}, {'&', ".-..."},
    {'*', "...-."}, {'(', "-.--."}, {')', "-.--.-"}, {'-', "-....-"}, {'_', "..--.-"},
    {'=', "-...-"}, {'+', ".-.-."}, {' ', "/"} // Other Characters

}; // holy fuuuuuuuuuuuuuuuck, this is one of the cases where AI is ACTUALLY useful

// HAHAHAHAH NO I'M NOT GONNA MANUALLY DO THAT AGAIN FOR THE MORSE-TO-TEXT ONE

unordered_map<string, char> InverDict(const unordered_map<char, string>& inPut) { // A function called InverDict that references the input as the constant parameter
    unordered_map<string, char> outPut; // The empty map that will eventually become the inverted map

    for (const auto& [key , value] : inPut) { // Range-based for-loop that unpacks a pair from the input to be utilized for the block below and does so until no more elements left, uses const auto& for efficiency
        outPut[value] = key; //This is the part where it inverts the elements
    }
    return outPut; // Outcomes the new inverted dictionary
}

unordered_map<string, char> ReverseDict = InverDict(Dict); // BEHOLD THE INVERTED DICTIONARY! Now usable as the Morse-To-Text Map

int main() {
    int Method;
    string Input, Result;

    cout << "Morse Code Translator \n";
    cout << "(0 = Text-To-Morse, 1 = Morse-To-Text) \n";
    cout << "Choose Method: ";

    while (!(cin >> Method) || Method < 0 || Method > 1) { //While loop that only allows 0 and 1 as input
        cout << "Invalid Input Try Again : ";
        cin.clear();
    }

    cout << "Enter Text: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Apparently you have to do this for getline to properly work in this case, due to the program reading the leftovers from the previous input
    getline(cin, Input);

    if (Method == 0) { //Text to Morse Code Translation Block
        for (char Charac: Input) { 
            if (Charac >= 'A' && Charac <= 'Z') { //Checks if the character is an upper case
                Charac = Charac + 32; //Upper Case Letter + 32 (ASCII) = Lower Case Letter
            }
            try { 
                Result += Dict.at(Charac); //Retrieves the associated morse code from the Dictionary based on the given character, then stores it in the Result 
            } catch (const out_of_range&) { 
                Result += Charac; //If an equivalent is not found, stores the original character instead
            }
            Result += " ";
        }

    } else { //Morse Code to Text Translation Block

        // Here we have my attempt at a Parser
        string Delimiter = " ";
        string Token;

        for (int i = 0; i <= Input.length(); ++i) {
        // If we hit a space OR the end of the string, process the current token
        if (i == Input.length() || Input[i] == ' ') {
            if (!Token.empty()) {
                // Use find() to avoid throwing exceptions
                auto it = ReverseDict.find(Token);
                
                if (!(it == ReverseDict.end())) {
                    Result += it->second; // If found, adds letter
                } else {
                    Result += '?'; // If not not found, stores '?' and keeps going
                }
                Token = ""; // Clear for the next Morse symbol
            }
        } else {
            // Build the token character by character (dots and dashes)
            Token += Input[i];
        }
    }
}

    cout << "Result : " << Result;

    return 0;
}
