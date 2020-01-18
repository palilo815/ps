#include<iostream>
using namespace std;

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    string s[2] = { " is NOT a multiple of "," is a multiple of " };
    int n, x;
    cin >> n;
    while (1) {
        cin >> x;
        if (x == 0) break;
        cout << x << s[x % n == 0] << n << ".\n";
    }
    return 0;
}