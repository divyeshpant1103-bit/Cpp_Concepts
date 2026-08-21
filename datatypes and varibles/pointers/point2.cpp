#include <iostream>
using namespace std;
int main(){
    int arr[5] = {1, 2, 3, 4, 5};
    int (*p)[5] = &arr;//here we passed the whole array int array of pointer
    for (int i = 0; i < 5;i++){
        cout << (*p)[i] << " ";
    }
    return 0;
}