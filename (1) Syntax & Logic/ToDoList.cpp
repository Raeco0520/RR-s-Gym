#include <iostream>
#include <vector> //Used for arrays that dynamically resizes and manages its own memory, avoiding manual memory management for lazy folks like me
#include <string>

using namespace std;

void PrintList(const string& PName, const vector<string>& PList) { //Uses const reference variables to avoid copying the entire list into memory every time it executes 
    cout << "\n \n \n";
    cout << "===================================\n";
    cout << PName << endl ;
    cout << "===================================\n";
    if (!PList.empty()) {
        for (const auto& iList:PList) { //Ranged-based For-Loops iterates through every element || Regular For-Loops are for certain controls within the iteration process
            cout << "* " << iList << endl ;
        }
    } else {
        cout <<"(Your List is Empty) \n";
    }
    cout << "===================================\n";
    cout << "(cmds: /delete, /clear, /break)\n";
    cout << "Add Task: ";
}


int main() {
    string ListName;
    string Input;
    vector<string> List; 

    cout << "TO DO LIST PROGRAM\n";
    cout << "Write List Name to Start : ";
    getline(cin, ListName); //cin only stores a single word, getline stores the entire line
    cout << endl;

    PrintList(ListName, List);

    while(getline(cin, Input)) { // Main Loop of the program, the user can input a task or use a command that performs a certain logic

        if (Input == "/break") { //Breaks out of the loop and concludes the program
            break;
        } else if (Input == "/delete") { //Deletes the last task, has an edge case since if you use pop_back in an empty vector, an error will happen.
            if (!List.empty()) {
                List.pop_back();
            } else {
                cout << "There is nothing to delete! \n";
                cout << "Try Again: ";
                continue;
            }
        } else if (Input == "/clear") { //Clears all the tasks
            List.clear();

        } else {
            List.push_back(Input); //Adds a new task into the list

        }

        PrintList(ListName, List);
    }

    return 0;
}

