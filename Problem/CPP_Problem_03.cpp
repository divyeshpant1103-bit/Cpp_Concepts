#include <iostream> 
using namespace std;
 class CoffeeMaker{
    private:
        int waterlevel;
        int beanlevel;
        double cash;
    public:
    CoffeeMaker(){
        waterlevel = 1000;
        beanlevel = 500;
        cash = 0.0;
    }
    void espresso(){
        if(waterlevel>= 50 && beanlevel >= 18){
            waterlevel -= 50;
            beanlevel -= 18;
            cash += 3.00;
            cout << "Espresso made. Enjoy!" << endl;
        } else {
            cout << "Not enough resources to make espresso." << endl;
        }
    }
    void americano(){
        if(waterlevel>= 150 && beanlevel >= 18){
            waterlevel -= 150;
            beanlevel -= 10;
            cash += 4.50;
            cout << "Americano made. Enjoy!" << endl;
        } else {
            cout << "Not enough resources to make americano." << endl;
        }
    }
    void restock(){
        waterlevel = 1000;
        beanlevel = 500;
        cout << "Coffee maker restocked." << endl;
    }
    void display(){
        cout << "Current water level: " << waterlevel << " ml" << endl;
        cout << "Current bean level: " << beanlevel << " g" << endl;
        cout << "Total cash collected: $" << cash << endl;
    }
 };
 int main(){
    CoffeeMaker cm;
    char choice;
    while(true){
        cout << "Press 'E' for espresso, 'A' for americano, 'R' to restock, D for display, or 'Q' to quit: ";
        cin >> choice;
        if(choice == 'E' || choice == 'e'){
            cm.espresso();
        }
        else if(choice == 'A' || choice == 'a'){
            cm.americano();
        }
        else if(choice == 'R' || choice == 'r'){
            cm.restock();
        }
        else if(choice == 'D' || choice == 'd'){
            cm.display();
            
        }
        else if(choice == 'Q' || choice == 'q'){
            cm.display();
            break;
        }
        else{
            cout << "Invalid input. Please try again." << endl;
            break;
        }
    }
 }