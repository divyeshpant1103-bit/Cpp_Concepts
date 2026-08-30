/*6.Define a class Hotel in C++ with the following specifications
Private members
• Rno Data member to store room number
• Name Data member to store customer name
• Tariff Data member to store per day charges
• NOD Data member to store number of days of stay
• CALC() Function to calculate and return amount as NOD*Tariff ,and if the value of days* Tariff
>10000,
then total amount is 1.05* days*Tariff.
Public members
• Checkin() Function to enter the content Rno, Name, Tariff and NOD
• Checkout() Function to display Rno, Name, Tariff,
NOD and Amount (amount to be displayed by calling function) CALC()*/

#include <iostream>
#include <string>
using namespace std;
class Hotel{
    private:
        int Rno;
        string Name;
        double Tariff;
        int NOD;
        int Calc(){
            int amount = NOD * Tariff;
            if(amount>10000){
                return 1.05 * amount;
            }else{
                return amount;
            }
        }
    public:
        void Checkin(){
            cout << "Enter Room Number: ";
            cin >> Rno;
            cin.ignore(); // To ignore the newline character after reading Rno
            cout << "Enter Customer Name: ";
            getline(cin, Name);
            cout << "Enter Tariff (per day charges): ";
            cin >> Tariff;
            cout << "Enter Number of Days of Stay: ";
            cin >> NOD;
        }
        void Checkout(){
            cout << "Room Number: " << Rno << endl;
            cout << "Customer Name: " << Name << endl;
            cout << "Tariff (per day charges): " << Tariff << endl;
            cout << "Number of Days of Stay: " << NOD << endl;
            cout << "Total Amount: " << Calc() << endl;
        }
};
int main(){
    Hotel member1;
    member1.Checkin();
    member1.Checkout();
    return 0;
}