#include <iostream>
using namespace std;
int& getvalue(int &x){
    return x;
}
int main(){
    int a = 5;
    int b= getvalue(a);
    b = 10;
    std::cout << "The value of a after modifying b is: " << a << std::endl;
    return 0;
}
// #include <iostream>
// using namespace std;

// int &getRef(int *arr, int index)
// {
//     return arr[index];
// }

// int main()
// {
//     int nums[] = {10, 20, 30, 40, 50};
//     getRef(nums, 2) = 99;

//     int &ref = getRef(nums, 4);
//     ref += 1;

//     cout << nums[2] << " " << nums[4] << endl;

//     return 0;
// }
// using namespace std;
// int& max(int &a,int &b,int &c){
//     int &max = a;//refrence variable to store the maximum value
//     if(max<b){
//         max = b;
//     }if(max<c){
//         max = c;
//     }
//     return max;
// }
// int main(){
//     int a, b, c;
//     cout << "Enter the three numbers:";
//     cin >> a >> b >> c;
//     int &ref=max(a, b, c);
//     cout << "The maximum number is: " << ref << endl;
//     ref = ref + 10;
//     cout << "The maximum number after adding 10 is: " << ref << endl;
//     return 0;
// }
