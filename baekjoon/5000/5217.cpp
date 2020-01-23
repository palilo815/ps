#include <iostream>
using namespace std;

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        cout << "Pairs for " << n << ':';
        for (int i = 1; i < n - i;++i) {
            if (i != 1) cout << ',';
            cout << ' ' << i << ' ' << n - i;
        }
        cout << '\n';
    }
    return 0;
}