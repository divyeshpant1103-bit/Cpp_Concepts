// #include <iostream>
// using namespace std;

// int main(){
//     int age;
//     char initial;

//     // Prompt the user to enter their age
//     cout << "Enter your age: ";
//     cin >> age;

//     // Use cin.ignore() to discard the newline character
//     cin.ignore(1);

//     // Prompt the user to enter the first letter of their name
//     cout << "Enter the first letter of your name: ";
//     cin >> initial;

//     // Display the entered age and initial
//     cout << "Your age is " << age << " and your initial is " << initial << endl;
//     return 0;
// }



// use of cin.ignore()
// #include <iostream>


// int main(){
//     std::cout << "Enter a sentence: ";

//     // Use cin.ignore() to skip up to 10 characters or until a space is encountered.
//     std::cin.ignore(10, ' ');
//     char nextChar;

//     // Read the next character from the input stream
//     std::cin >> nextChar;

//     // Output the character that was read after ignoring the specified characters
//     std::cout << "Next character after ignoring: " << nextChar << std::endl;

//     return 0;
// }


//use of cin.fail()
// C++ program to use cin.fail() method

#include <iostream>
#include <limits>
using namespace std;

int main()
{
    // Declare and initialize integer variables.
    int i = 0, j = 0;

    // Infinite loop to continually ask for input until a
    // valid integer is entered.
    while (true) {
        // Ask the user to enter int value.
        cout << "Enter an Integer: " << endl;

        i++;

        // Read input from the user.
        cin >> j;

        // Check if the input operation failed (i.e., input
        // was not an integer).
        if (cin.fail()) {
            // Clear the error flags on the input stream.
            cin.clear();

            // leave the rest of the line
            cin.ignore(numeric_limits<streamsize>::max(),
                       '\n');

            // Ask the user to enter a valid int number only
            cout << "Wrong input, please enter a number: ";
        }
        else {
            // Print the valid integer entered by the user.
            cout << "Integer " << i << ": " << j << endl;
        }
    }
    return 0;
}