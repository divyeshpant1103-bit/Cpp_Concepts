// Wap to perform aritmetic operation on data member of 2 object of same class and store result in another object of same class
#include <iostream>
using namespace std;
class Arithmetic{
    
    private:
        int num;
    public:
        Arithmetic(int n){
            num = n;
        }
        void set_num(int n){
            num = n;
        }
        int get_num(){
            return num;
        }
        friend Arithmetic add(Arithmetic, Arithmetic);
        friend Arithmetic subtract(Arithmetic, Arithmetic);
        friend Arithmetic multiply(Arithmetic, Arithmetic);
        friend Arithmetic divide(Arithmetic, Arithmetic);
};
Arithmetic add(Arithmetic obj1, Arithmetic obj2){
    return Arithmetic(obj1.num + obj2.num);
}
Arithmetic subtract(Arithmetic obj1, Arithmetic obj2){
    return Arithmetic(obj1.num - obj2.num);
}
Arithmetic multiply(Arithmetic obj1, Arithmetic obj2){
    return Arithmetic(obj1.num * obj2.num);
}
Arithmetic divide(Arithmetic obj1, Arithmetic obj2){
    if(obj2.num != 0){
        return Arithmetic(obj1.num / obj2.num);
    } else {        
        cout << "Division by zero is not allowed." << endl;
        return Arithmetic(0);
    }   
}
int main(){
    Arithmetic obj1(10);
    Arithmetic obj2(5);
    Arithmetic result(0);
    result = add(obj1, obj2);
    cout << "Sum: " << result.get_num() << endl;
    result = subtract(obj1, obj2);
    cout << "Difference: " << result.get_num() << endl;
    result = multiply(obj1, obj2);
    cout << "Product: " << result.get_num() << endl;
    result = divide(obj1, obj2);
    cout << "Quotient: " << result.get_num() << endl;
    return 0;
}
