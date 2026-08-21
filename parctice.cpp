// //program for the prime or not
// #include <iostream>
// using namespace std;
// int main(){
//     int num;
//     cout<<"Enter the number";
//     cin>>num;
//     int isprime=1;
//     if(num<2){
//         isprime=0;
//     }
//     for(int i=2;i<=num/2;i++){
//         if(num%i==0){
//             isprime=0;
//             break;
//         }
//     }
//     if(isprime==1){
//         cout<<"primenumber"<<endl;
//     }else{
//         cout<<"Notprime";
//     }
//     return 0;
// }
#include <iostream>
using namespace std;
int main(){
    int n;
    cout<<"ENter the  limit";
    cin>>n;
    for(int i=0;i<n;i++){
       for(int j=i;j<n;j++){
        cout<<(char)('A'+j);
        
       }

       cout<<endl;
    }
}