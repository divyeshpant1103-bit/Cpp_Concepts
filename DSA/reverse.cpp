#include <iostream>
using namespace std;
void reverse(int arr[],int size) {
    int start=0;
    int end=size-1;
    while(start<=end){
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}
int main()
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    reverse(arr, 10);
    //after reverse
    for (int i = 0; i < 10;i++){
        cout << arr[i] << " ";
    }
}