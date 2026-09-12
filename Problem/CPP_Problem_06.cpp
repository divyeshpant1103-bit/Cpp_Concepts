// wap to perform arithmeitc operation on data member of 2 different classes and store result in dm of 3rd classs.Friend function id mf of 3rd class
#include <iostream>
using namespace std;
class ClassB;
class ClassA{
    private:
        int a;
        public:
        ClassA(int x){
            a = x;
        }
        friend class ClassC; // Declare ClassC as a friend class
};
class ClassB{
    private:
        int b;
    public:
        ClassB(int y){
            b = y;
        }
        friend class ClassC; // Declare ClassC as a friend class
};
class ClassC{
    private:
        int c;
    public:
        void add(ClassA obj1, ClassB obj2){
            c = obj1.a + obj2.b;
            cout << "Sum of ClassA and ClassB objects: " << c << endl;
        }
        void subtract(ClassA obj1, ClassB obj2){
            c = obj1.a - obj2.b;
            cout << "Difference of ClassA and ClassB objects: " << c << endl;
        }
        void multiply(ClassA obj1, ClassB obj2){
            c = obj1.a * obj2.b;
            cout << "Product of ClassA and ClassB objects: " << c << endl;
        }
        void divide(ClassA obj1, ClassB obj2){
            if(obj2.b != 0){
                c = obj1.a / obj2.b;
                cout << "Quotient of ClassA and ClassB objects: " << c << endl;
            } else {
                cout << "Division by zero is not allowed." << endl;
            }
        }
};
int main(){
    ClassA obj1(10);
    ClassB obj2(20);
    ClassC obj3;
    obj3.add(obj1,obj2);
    obj3.subtract(obj1,obj2);
    obj3.multiply(obj1,obj2);
    obj3.divide(obj1,obj2);
    return 0;
}