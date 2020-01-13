#include<iostream>
using namespace std;

int main()
{
    int n, sign;
    cin >> n;
    if (n > 0)sign = 1;
    else if (n == 0) sign = 0;
    else sign = -1;
    n *= sign;
    int* arr = new int[n + 2];
    arr[0] = 0, arr[1] = 1;
    if (sign >= 0) {
        for (int i = 2; i <= n; i++) {
            arr[i] = arr[i - 1] + arr[i - 2];
            if (arr[i] >= 1000000000)
                arr[i] %= 1000000000;
        }
    }
    else {
        for (int i = 2; i <= n; i++) {
            arr[i] = arr[i - 2] - arr[i - 1];
            if (arr[i] >= 1000000000 || arr[i] <= -1000000000)
                arr[i] %= 1000000000;
        }
    }
    if (arr[n] > 0)sign = 1;
    else if (arr[n] == 0) sign = 0;
    else sign = -1;
    cout << sign << endl << sign * arr[n];
    return 0;
}