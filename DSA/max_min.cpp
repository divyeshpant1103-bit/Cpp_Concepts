#include <iostream>
using namespace std;
int main(){
    int num[100];
    int n;
    cout << "Enter the limit";
    cin >> n;
    for (int i = 0; i < n;i++){
        cin >> num[i];
    }
    int maxi = INT_MIN;
    int mini = INT_MAX;
    for (int i = 0; i <n ;i++){
        maxi = max(maxi, num[i]);//predefiend function for max
        // if (max < num[i])
        // {
        //     max = num[i];
        // }
        // if(min>num[i]){
        //     min = num[i];
        // }
        mini = min(mini, num[i]);
    }
    cout << maxi<<mini;
    return 0;
}