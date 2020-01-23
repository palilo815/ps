#include<iostream>
using namespace std;

int main()
{
    int arr[8];
    for (int i = 0; i < 8; i++)
        cin >> arr[i];
    bool Ascending = (arr[1] > arr[0]);
    for (int i = 1;i < 7;i++) {
        if (Ascending != (arr[i + 1] > arr[i])) {
            cout << "mixed";
            return 0;
        }
    }
    if (Ascending) cout << "ascending";
    else cout << "descending";
    return 0;
}