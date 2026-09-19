// write a cpp program to overload the following unary operator
// negation
// pre increment
// pre decrement using friend function
#include <iostream>
using namespace std;
class Number
{
private:
    int value;

public:
    Number(int v)
    {
        value = v;
    }
    void operator-()
    {
        value = -value;
    }
    void display()
    {
        cout << "Value: " << value << endl;
    }
    void operator++()
    {

        ++value;
    }
    friend void operator--(Number &obj);
};
void operator --(Number &obj)
{
    --obj.value;
}
int main()
{
    Number num(5);
    cout << "Original ";
    num.display();
    -num;
    --num;
    cout << "Negated ";
    num.display();
    Number num2(10);
    cout << "Original ";
    num2.display();
    ++num2;
    ++num;
    num.display();
    cout << "After Pre-increment ";
    num2.display();
    Number num3(15);
    cout << "Original ";
    num3.display();
    --num3;
    cout << "After Pre-decrement ";
    num3.display();
    return 0;
}
