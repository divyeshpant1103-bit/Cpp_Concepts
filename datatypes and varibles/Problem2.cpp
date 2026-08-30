/*Q7. Implement a Program in C++ by defining a class to represent a bank account.
Include the following:
Data Members
● Name of the depositor
● Account number
● Type of account (Saving, Current etc.)
● Balance amount in the account
Member Functions
● To assign initial values
● To deposit an amount
● To withdraw an amount after checking the balance
● To display name and balance
*/
#include <iostream>
#include <string>
using namespace std;
class BankAccount{
    private:
        string depositer_name{"User"};
        string account_number{"000000000"};
        string account_type{"Saving"};
        double balance_amount{0.0};
        public:
        BankAccount(string name, string acc_num, string acc_type, double balance){
            depositer_name = name;
            account_number = acc_num;
            account_type = acc_type;
            balance_amount = balance;
        }
        BankAccount() = default;
        void deposit(double amount){
            if(amount >0){
                balance_amount += amount;
                cout<<"Deposited: "<<amount<<endl;
            }else{
                cout<<"Invalid deposit amount!"<<endl;
            }
        }
        void withdraw(double amount){
            if (amount > 0 && amount<=balance_amount){
                balance_amount -= amount;
                cout<<"Withdrawn: "<<amount<<endl;
            }else{
                cout<<"Invalid withdraw amount or insufficient balance!"<<endl;
            }
        }
        void display(){
            cout<<"Depositer Name: "<<depositer_name<<endl;
            cout<<"Balance Amount: "<<balance_amount<<endl;
        }
};

int main(){
    BankAccount account1("John Doe", "123456789", "Saving", 1000.0);
    account1.display();
    account1.deposit(500);
    account1.display();
    account1.withdraw(200);
    account1.display();
    account1.withdraw(2000); // Test insufficient balance
    cout << endl;
    BankAccount account2; // Default constructor
    account2.display();
    return 0;
}