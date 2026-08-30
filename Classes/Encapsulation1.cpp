/*
Create a simple Banking Application that demonstrate the concept of Ecapsulation
   Employee Bank Account class customer detailand provide secure acces to operaation
   Each account should have 
    1.acc holder
    2.unique account number
    3curr balance
functions
1.deposit
2.withdraw
3check balaance4Add constcuptr to initialize an account with a min balance of 500
add proper validation while performing operation
*/

#include <iostream>
using namespace std;
int globalcounter = 1000;

class Bank_account{
    private:
        string acc_holder;
        int acc_number;
        double curr_balance;
    public:
       Bank_account(string name,double balance=500.00){
           acc_holder =name;
           curr_balance = balance;
           acc_number = globalcounter++;
           if(balance<500){
               cout << "Initial balance is less than minimum required balance of 500. Setting balance to 500." << endl;
               balance = 500.00;
           }
           else
           {
               curr_balance = balance;
           }
       }
       void deposit(double amount){
        if(amount>0){
            curr_balance=curr_balance+amount;
            cout << "Amount deposited successfully. Current balance: " << curr_balance << endl;
        }else{
            cout << "Invalid deposit amount. Please enter a positive value." << endl;
        }
    }
        void withdraw(double amount){
            if(amount>0 &&amount<=curr_balance){
                curr_balance=curr_balance-amount;
                cout << "Amount withdrawn successfully. Current balance: " << curr_balance << endl;
            }else{
                cout << "Invalid withdrawal amount. Please enter a positive value less than or equal to the current balance." << endl;
            }
        }
        double get_balance()
        {
            return curr_balance;
        }
        void display(){
            cout << "Account Holder: " << acc_holder << endl;
            cout << "Account Number: " << acc_number << endl;
            cout << "Current Balance: " << curr_balance << endl;
        }
};
int main(){
    Bank_account account1("Divyesh", 1000.00);
    account1.display();
    account1.deposit(500.00);
    account1.withdraw(200.00);
    account1.withdraw(2000.00); // Invalid withdrawal
    account1.deposit(-100.00); // Invalid deposit
    account1.display();
    Bank_account account2("John", 300.00); // Balance less than minimum
    account2.display();
    return 0;
}
