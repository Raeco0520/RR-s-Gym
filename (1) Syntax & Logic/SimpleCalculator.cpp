#include <iostream> // For cout & cin
#include <limits> // Includes numeric_limits<streamsize>::max() which is important for discarding ALL characters from the buffer
using namespace std; // Makes typing easier, okay for simple projects

int main() { 
    double x , y ; 
    string validOperator = "+-*/" ; // A list of characters that validates the operator input
    char Operator ; 

    cout << "Simple Calculator\n" ;

    cout << "1st Number: " ; 
    while (!(cin >> x)) { // This loops until the user inputs the correct data type (double)
        cout << "Invalid Input Try Again : ";
        cin.clear(); // Resets the input so it can accept new input
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // while cin.ignore(100, '\n') can technically work, this one guarantees a full clean up
    }


    cout << "Operator ( + - * / ): " ;
    while (!(cin >> Operator) || (validOperator.find(Operator) == string::npos)) { //Same as the other Loop (char), but also checks if the character exists from the list; npos means 'not found'. 
        cout << "Invalid Input Try Again : ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "2nd Number : " ;
    while (!(cin >> y)) {
        cout << "Invalid Input Try Again : ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch (Operator) { //Once y has been inserted, the program selects the case with the same character as the Operator, and outputs the related expression
        case '+' :
        cout << "Your Result is : " << x + y ;
        break;

        case '-' :
        cout << "Your Result is : " << x - y ;
        break;

        case '*' :
        cout << "Your Result is : " << x * y ;
        break;

        case '/' :
        if (y != 0 ) // This condition is necessary as the program will cry if you force it to divide something by zero
            cout << "Your Result is : " << x / y ; 
        else 
            cout << "Cannot divide by Zero!"; 
        break;
              
    }

    return 0;

}