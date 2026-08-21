//BRUTE FORCE TECHNIQUE
#include <iostream>
using namespace std;
void unique_element(int arr[], int n)
{
    int count;
    for (int i = 0; i < n; i++)
    {
        count = 0;
        for (int j = 0; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                count++;
            }
        }
        if (count == 1)
        {
            cout << arr[i]<<" ";
        }
    }
}
int main()
{
    int arr[11] = {2, -1, 2, 3, 3, 7, 7, 8, 8, 9, 5};
    unique_element(arr, 11);
}