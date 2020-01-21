#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int a, b, c;
    while (cin >> a >> b >> c)
        cout << max(b - a, c - b) - 1 << '\n';
    return 0;
}