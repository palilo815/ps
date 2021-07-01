#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        vector<int> a(n);
        for (auto& x : a) cin >> x;

        for (int i = 0; i < n - 1; ++i)
            a[i] = abs(a[i] - a[i + 1]);
        a.pop_back();

        if (none_of(a.begin(), a.end(), [&](const auto& x) { return x; })) {
            cout << "INFINITY\n";
        } else {
            cout << accumulate(a.begin(), a.end(), 0, [&](const auto& sum, const auto& x) { return gcd(sum, x); }) << '\n';
        }
    }
}