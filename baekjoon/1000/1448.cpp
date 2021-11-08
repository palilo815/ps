#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    sort(a.begin(), a.end(), greater());
    for (int i = 0; i + 2 < n; ++i) {
        if (a[i] < a[i + 1] + a[i + 2]) {
            return cout << a[i] + a[i + 1] + a[i + 2], 0;
        }
    }
    cout << -1;
}