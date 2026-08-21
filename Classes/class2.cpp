#include <iostream>
using namespace std;
#define PI 3.14
class Cylinder{
    public:
    //Member Variables
        double base_radius{1.0};
        double height{1};
    public:
        double volume(){
            return PI * base_radius * base_radius * height;
        }
};

int main(){
    Cylinder cylinder1;//object
    cout << "volume c1 :" << cylinder1.volume() << endl;
    //change variables
    cylinder1.base_radius = 3.0;
    cylinder1.height = 2;
    cout << "volume c1 :" << cylinder1.volume() << endl;
    cylinder1.height = 3;
    cout << "volume c1 :" << cylinder1.volume() << endl;
    Cylinder cylinder2;//object
    cout << "volume c2 :" << cylinder2.volume() << endl;
    return 0;
}