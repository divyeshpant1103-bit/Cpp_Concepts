// #include <iostream>
// using namespace std;

// bool search(int arr[], int n, int key){
//     for (int i = 0; i < n;i++){
//         if(arr[i]==key){
//             return 1;
//         }
//     }
//     return 0;
// }

// int main(){
//     int size;
//     int arr[10] = {5, 7, -2, 10, 22, -2, 0, 5, 22, 1};
//     cout << "Enter the key" << endl;
//     cin >> size;
//     bool found = search(arr, 10, size);
//     if(found){
//         cout << "key is present";
//     }else{
//         cout << "key is not present";
//     }
// }
#include <iostream>
using namespace std;
int main(){
    int x;
    cout << "Enter the pattern limit";
    cin >> x;
    for (int i = 0; i < x;i++){
        for (int j = i; j < x;j++){
            cout << "*";
        }
        cout << endl;
    }
        return 0;
}