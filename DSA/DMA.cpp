#include <iostream>
using namespace std;
int *modifyvalue3()
{
    int num = 15;
    cout << "x (Inside function) = " << num << endl;
    return &num; /*The varible shows the undefineds behaviour
     because the scope of the num is inside the function and can act as the danglaing pointer*/
}
//----------------------- modification can be done by using the global varibale or the static varibalr or assiigning the value by the DMA ----------------------------------------------

int *modifyvalue2()
{
    static int num = 15; // The static variable will be stored in the data segment and will not be destroyed after the function call
    cout << "x (Inside function) = " << num << endl;
    return &num;
}

int num = 15; // The global variable will be stored in the data segment and will not be destroyed after the function call
int *modifyvalue()
{
    cout << "x (Inside function) = " << num << endl;
    return &num;
}


//using the dynamic memory allocation we can also modify the value of the variable and it will not be destroyed after the function call
void *modifyvalue1()
{
    int *num = new int(15);
    cout << "x (Inside function) = " << *num << endl;
}


int main()
{
    int x = 10;
    cout << "x (Before function call) = " << x << endl;
    modifyvalue();
    modifyvalue1();
    modifyvalue3();
    modifyvalue2();
    cout << "x (After function call) = " << x << endl;
    return 0;
}