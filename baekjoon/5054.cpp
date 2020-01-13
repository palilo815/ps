#include<iostream>
using namespace std;

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int t, n, x;
    cin >> t;
    while (t-- > 0) {
        cin >> n;
        int L = 100, R = 0;
        while (n-- > 0) {
            cin >> x;
            if (x < L) L = x;
            if (x > R) R = x;
        }
        cout << 2 * (R - L) << '\n';
    }
    return 0;
}