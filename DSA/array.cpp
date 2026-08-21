// #include <iostream>  
// using namespace std;
// // void printarray(int arr[],int size){
// //     for (int i = 0; i < size;i++){
// //         cout << arr[i]<<" ";
// //     }
// //     cout << "printing done"<< endl;
// // }
// int main(){
//     int first[10] = {10};
//     int n = 8;
//     printarray(first, n);
//     int fifth[10] = {90};
//     printarray(fifth, 10);
//     int size = sizeof(fifth) / sizeof(int);
//     cout << size << endl;
//     int second[20] = {2, 3};
//     size = sizeof(second) / sizeof(int);
//     cout << size;// I have to explicitly send the size of the array if the size is not same to the length of array

//     return 0;
// }
// scope of the array;
#include <iostream>
using namespace std;
void update(int arr[],int n){
    cout << "INSIDE the FUnction" << endl;
    
    //updating the array
    arr[0] = 120;
    for (int i = 0; i < n;i++){
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "SENDING THE ARRAY BACK ";
}
int main(){
    int arr[3] = {1, 2, 3};
    update(arr, 3);
    // printing the array
    for (int i = 0; i < 3; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}