#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// work in progress

int main() {
    string ListName;
    string Input;
    vector<string> List;

    cout << "TO DO LIST PROGRAM\n";
    cout << "Write List Name to Start : ";
    cin >> ListName;
    cout << endl;



    /*
    cin >> Input;
    List.push_back(Input);
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    */

    return 0;
}





/*

    cout << "[ " << ActionPlaceHolder << " ] \n" ;
    cout << "====================================\n";
    cout << ListName << endl;
    cout << "====================================\n";
    for(string iList:List) {
        cout << "*" << iList << endl;
    }

TO DO LIST PROGRAM
Plan to use
getline(cin, input)
clear() : Deletes all the bulletpoints
pop back() : Delete latest bullet point
push back() : Add new bulletpoint
empty(): Checks if the list is empty
begin() & end() : For iterating


PSEUDO CODE PLAN

instead of only cin, use getline(cin, input) to capture the whole line

User must write the list name to start the program

if user inputs "/delete", it deletes the most recent bullet point
if user inputs "/clear", it clears all the bulletpoints
    if there is no bulletpoints to delete, the program states that there is nothing to delete

Every time the user enters a string, it adds as the latest bulletpoint
and the program displays the title name reiterates from the oldest to the newest bulletpoint
    If the input is an empty string, it will not be added as a new bulletpoint

For more clarity, the action name is stated at the start after every successful input

To get out of the program, user inputs "/break"

*/

