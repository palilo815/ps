#include<iostream>
using namespace std;

int main()
{
    int n; cin >> n;
    if (n % 2)
        cout << (1 + n / 2) * (1 + n / 2);
    else
        cout << (1 + n / 2) * (2 + n / 2);
    return 0;
}