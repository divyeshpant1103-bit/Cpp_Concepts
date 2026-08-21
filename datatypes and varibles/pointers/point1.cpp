#include <iostream>
using namespace std;
void swap(int a,int b){
    int temp = a;
    a = b;
    b = temp;
    cout << "after swapping :" << a <<" " << b;
}



int main(){
    int a = 9;
    int b = 10;
    cout << "before swapping" << a <<" "<< b;
    swap(a, b);
    cout << "after swappping" << a <<" "<< b;
    return 0;
}




void swap(int *a,int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
    cout << "INside function" << *a << " " << *b;
}



int main()
{
    int a = 9;
    int b = 10;
    cout << "before swapping" << a << " " << b;
    swap(&a, &b);
    cout << "after swappping" << a << " " << b;
}