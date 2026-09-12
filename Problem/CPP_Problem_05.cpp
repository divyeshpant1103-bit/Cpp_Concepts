// wap to perfroem arithmetic operation on object of 2 different classes using fried function(as member function of second class)
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
        friend void add(ClassA,ClassB);
        friend class ClassB; // Declare ClassB as a friend class
        
};
class ClassB{
    private:
        int b;  
        public:
        ClassB(int y){
            b = y;
        }
        friend void add(ClassA,ClassB);
};
void add(ClassA obj1,ClassB obj2){
    int sum = obj1.a + obj2.b;
    cout << "Sum of ClassA and ClassB objects: " << sum << endl;
}
int main(){
    ClassA obj1(10);
    ClassB obj2(20);
    add(obj1,obj2);
    return 0;