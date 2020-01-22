#include<iostream>
using namespace std;

int main()
{
    int n, x, y;
    cin >> n;
    while (n--) {
        cin >> x >> y;
        if (x == y) {
            if (x % 2 == 0) cout << x * 2;
            else cout << (x - 1) * 2 + 1;
        }
        else if (x == y + 2) {
            if (x % 2 == 0) cout << x * 2 - 2;
            else cout << (x - 1) * 2 - 1;
        }
        else cout << "No Number";
        cout << '\n';
    }
    return 0;
}