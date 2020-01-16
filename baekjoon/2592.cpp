#include<iostream>
using namespace std;

int arr[101];
int main()
{
    int sum = 0, x, M = 10;
    while (M--) {
        cin >> x;
        x /= 10;
        sum += x;
        ++a[x];
    }
    cout << sum << '\n';
    M = 0;
    for (int i = 1; i < 101; ++i)
        if (a[i] > a[M]) M = i;
    cout << M * 10;
    return 0;
}