#include<iostream>
using namespace std;

int main()
{
    int n; cin >> n;
    cout << n * (n - 1) * (n - 2) * (n - 3) / 4 / 3 / 2;
    return 0;
}