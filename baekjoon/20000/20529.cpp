#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    if (n > 32) {
        string s;
        getline(cin, s), getline(cin, s);
        cout << "0\n";
        return;
    }

    vector<int> a(n);
    char s[5];
    for (int i = 0; i < n; ++i) {
        cin >> s;
        a[i] = (s[0] == 'E') << 3 | (s[1] == 'S') << 2 | (s[2] == 'T') << 1 | (s[3] == 'J');
    }

    int mn = INT_MAX;
    for (int i = 0; i < n - 2; ++i)
        for (int j = i + 1; j < n - 1; ++j)
            for (int k = j + 1; k < n; ++k)
                mn = min(mn, __builtin_popcount(a[i] ^ a[j]) + __builtin_popcount(a[j] ^ a[k]) + __builtin_popcount(a[k] ^ a[i]));
    cout << mn << '\n';
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--)
        solve();
}