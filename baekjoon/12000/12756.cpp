#include <iostream>
using namespace std;

int main()
{
    int a1, h1, a2, h2;
    cin >> a1 >> h1 >> a2 >> h2;
    while (h1 > 0 && h2 > 0)
        h1 -= a2, h2 -= a1;
    if (h1 <= 0 && h2 <= 0) cout << "DRAW";
    else if (h1 <= 0) cout << "PLAYER B";
    else cout << "PLAYER A";
    return 0;
}