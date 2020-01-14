#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
    int a, b, c;
    cin >> a >> b >> c;
    if (a == b) {
        if (a == c) cout << 10000 + a * 1000;
        else cout << 1000 + a * 100;
    }
    else {
        if (a == c) cout << 1000 + a * 100;
        else {
            if (b == c) cout << 1000 + b * 100;
            else {
                int x = max(a, b);
                x = max(x, c);
                cout << x * 100;
            }
        }
    }
    return 0;
}