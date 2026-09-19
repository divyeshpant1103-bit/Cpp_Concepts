//wap that contain 2 classes "bank" and "account"
//data member of bank=bankname,username,userID,balance
//account=deposit(),withdraw()showdetail()

//write a cpp program to overload the following unary operator
//negation
//pre increment
//pre decrement using friend function

#include <iostream>
#include <string>
using namespace std;
class Account;//forward declartion
class Bank{
    private:
        string bankname;
        string username;
        int userID;
        double balance;
    public:
        Bank(string bname,string uname,int uid,double bal){
            bankname = bname;
            username = uname;
            userID = uid;
            balance = bal;
        }
    void set_bankname(string bname){
        bankname = bname;
    }
    void set_username(string uname){
        username = uname;
    }
    void set_userID(int uid){
        userID = uid;
    }
    void set_balance(double bal){
        balance = bal;
    }
    string get_bankname(){
        return bankname;
    }
    string get_username(){
        return username;
    }
    int get_userID(){
        return userID;
    }
    double get_balance(){
        return balance;
    }
    friend class Account; // declare account as friend class
};
class Account{
    
    public:
        void deposit(Bank &obj,double amount){
            obj.balance += amount;
            cout << "Deposited: " << amount << endl;
        }
        void withdraw(Bank &obj,double amount){
            if(obj.balance >= amount){
                obj.balance -= amount;
                cout << "Withdrawn: " << amount << endl;
            } else {
                cout << "Insufficient balance." << endl;
            }
        }
        void showdetail(Bank obj){
            cout << "Bank Name: " << obj.bankname << endl;
            cout << "Username: " << obj.username << endl;
            cout << "User ID: " << obj.userID << endl;
            cout << "Balance: " << obj.balance << endl;
        }
};
int main(){
    Bank obj1("SBI","John",12345,1000.0);
    Account obj2;
    cout << "Initial Balance: " << obj1.get_balance() << endl;
    obj2.deposit(obj1, 500.0);
    obj2.withdraw(obj1,200.0);
    obj2.showdetail(obj1);
    return 0;
}