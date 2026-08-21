#include <iostream>
using namespace std;

void duplicate(int arr[], int n)
{
    bool visited[n] = {false};
    for (int i = 0; i < n; i++)
    {
        if (visited[i])
            continue; // already processed
        int count = 1;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                count++;
                visited[j] = true; // mark so we skip it later
            }
        }
        if (count > 1)
        {
            cout << arr[i] << " ";
        }
    }
}

int main()
{
    int arr[8] = {4, 1, 2, 4, 3, 2, 7, 1};
    duplicate(arr, 8);
}