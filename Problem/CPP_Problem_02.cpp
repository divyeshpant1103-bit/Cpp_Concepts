/*Question:
Imagine a ticket stand at a local fair with a class called TicketStand. The two data items are of type unsigned int and double to hold the total number of people admitted and the total amount of money collected.
A constructor initializes both of these data members to 0. A member function called adultTicket() increments the people total by 1 and adds 12.50 to the cash total. Another function called childTicket() increments the people total by 1 but adds only 5.00 to the cash total. Finally, a member function called display() shows the two totals.
Include a program to test this class. This program should allow the user to push 'A' to count an adult ticket and 'C' to count a child ticket. Pushing the 'Q' (Quit) key should cause the program to print out the total number of people and total cash, and then exit.
*/
#include <iostream>
#include <string>
using namespace std;
class TicketStand
{
private:
    unsigned int people;
    double ticket_price;

public:
    TicketStand()
    {
        people = 0;
        ticket_price = 0.0;
    }

    void adultTicket(){
        people = people + 1;
        ticket_price = ticket_price + 12.50;
    }
    void childTicket(){
        people = people + 1;
        ticket_price = ticket_price + 5.00;
    }
    void display(){
        cout << "Total number of people: " << people << endl;
        cout << "Total cash collected: $" << ticket_price << endl;
    }
};
int main(){
    TicketStand Stand1;
    char choice;
    cout<<"Press 'A' for adult ticket, 'C' for child ticket, or 'Q' to quit: ";
    while(true){
        cin >> choice;
        if(choice == 'A' || choice == 'a'){
            Stand1.adultTicket();
        }
        else if(choice == 'C' || choice == 'c'){
            Stand1.childTicket();
        }
        else if(choice == 'Q' || choice == 'q'){
            Stand1.display();
            break;
        }
        else{
            cout << "Invalid input. Please try again." << endl;
            break;
        }
    }
}