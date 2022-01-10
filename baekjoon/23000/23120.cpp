#include <bits/stdc++.h>

int main() {
    using namespace std;
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int n;
    cin >> n;
    vector<int> a(n);
    iota(a.begin(), a.end(), 0);
    cout << "? " << n;
    for (int i = 1; i <= n; ++i) {
        cout << ' ' << i;
    }
    cout << endl;
    int m;
    cin >> m;
    auto ask = [&]() {
        shuffle(a.begin(), a.end(), rng);
        cout << "? " << n / 2;
        for (int i = 0; i < n / 2; ++i) {
            cout << ' ' << a[i] + 1;
        }
        cout << endl;
        int m1;
        cin >> m1;
        cout << "? " << n - n / 2;
        for (int i = n / 2; i < n; ++i) {
            cout << ' ' << a[i] + 1;
        }
        cout << endl;
        int m2;
        cin >> m2;
        return (m - (m1 + m2)) & 1;
    };
    for (int i = 0; i < 29; ++i) {
        if (ask()) {
            return cout << "! NO" << endl, 0;
        }
    }
    cout << "! YES" << endl;
}
