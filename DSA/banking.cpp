#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
struct bank
{
    int AccountNumber;
    string Name;
    string AccountType;
    float Balance;
    float InterestRate;

    float getbalance()
    {
        return 0;
    }
    int getAccountNumber()
    {
        return 10000+rand();
    }
    void CreateAccount() {
        AccountNumber=getAccountNumber();
        cout << "Enter the name of the account holder: ";
        getline(cin, Name);
        cout << "Enter the account type (Savings/Current): ";
        getline(cin, AccountType);
        Balance = getbalance();
        cout << "Account created successfully!" << endl;
    }
    void DisplayAccountDetails() {
        cout << "Account Number: " << AccountNumber << endl;
        cout << "Account Holder Name: " << Name << endl;
        cout << "Account Type: " << AccountType << endl;
        cout << "Balance: $" << Balance << endl;
    }
    void Deposit(float amount) {
        if(amount >0){
            Balance += amount;
            cout<<"Deposited successfully! New balance: $" << Balance << endl;
        }else{
            cout << "Deposit amount must be positive." << endl;
        }
    }
    void Withdraw(float amount){
        if(amount>  0 &&amount<=Balance){
            Balance = Balance - amount;
        }else{
            cout << "Insufficient balance or invalid amount." << endl;
        }
    }
    void CalculateInterest() {
        if (AccountType == "Savings") {
            InterestRate = 0.04; // 4% interest for savings account
        } 
        else {
            cout << "Invalid account type." << endl;
            return;
        }
        float interest = Balance * InterestRate;
        Balance += interest;
        cout << "Interest of $" << interest << " added. New balance: $" << Balance << endl;
    }
    void searchAccount(int accNum){
        if(accNum==AccountNumber){
            DisplayAccountDetails();
        }
        else{
            cout << "Account not found." << endl;
        }
    }
    void removeAccount(int accNum){
        if(accNum==AccountNumber){
            AccountNumber=0;
            Name="";
            AccountType="";
            Balance=0;
            InterestRate=0;
            cout << "Account removed successfully." << endl;
        }
        else{
            cout << "Account not found." << endl;
        }
    }
};
int main()
{
    bank b;
    do{
        
    }
    int searchAccNum;
    cout << "Enter account number to search: ";
    cin >> searchAccNum;
    b.searchAccount(searchAccNum);
    int removeAccNum;
    cout << "Enter account number to remove: ";
    cin >> removeAccNum;
    b.removeAccount(removeAccNum);
    return 0;
}
