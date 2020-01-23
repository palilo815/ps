#include<iostream>
using namespace std;

bool HW[30];
int main()
{
    int T = 28, n;
    while (T--) {
        cin >> n;
        HW[n - 1] = true;
    }
    for (int i = 0;i < 30;i++)
        if (!HW[i])
            cout << i + 1 << '\n';
    return 0;
}