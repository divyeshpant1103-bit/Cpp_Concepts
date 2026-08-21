#include <iostream>
using namespace std;
void swappairs(int arr[], int n)
{
    int start = 0;
    int end = 1;
    while (start < end && end < n)
    {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start = start + 2;
        end = start + 1;
    }
}
int main()
{
    int num[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    swappairs(num, 10);
    for (int i = 0; i < 10; i++)
    {
        cout << num[i] << " ";
    }
}
