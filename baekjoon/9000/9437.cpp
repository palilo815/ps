#include <iostream>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, p;
    while (cin >> n) {
        if (n == 0) break;
        cin >> p;
        if (p <= n / 2) {
            if (p % 2) cout << p + 1 << ' ' << n - p << ' ' << n - p + 1;
            else cout << p - 1 << ' ' << n - p + 1 << ' ' << n - p + 2;
        }
        else {
            if (p % 2) cout << n - p << ' ' << n - p + 1 << ' ' << p + 1;
            else cout << n - p + 1 << ' ' << n - p + 2 << ' ' << p - 1;
        }
        cout << '\n';
    }
    return 0;
}