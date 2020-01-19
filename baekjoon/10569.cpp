#include<iostream>
using namespace std;

int main()
{
    int t, v, e;
    cin >> t;
    while (t--) {
        cin >> v >> e;
        cout << 2 - v + e << '\n';
    }
    return 0;
}