#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, s, p;
    cin >> n >> s >> p;
    vector a(p, -1);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    if (upper_bound(a.begin(), a.end(), s, greater()) == a.end()) {
        cout << -1;
    } else {
        cout << lower_bound(a.begin(), a.end(), s, greater()) - a.begin() + 1;
    }
}