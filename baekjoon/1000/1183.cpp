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
    if (n & 1) return cout << 1, 0;
    vector<int> a(n);
    for (auto& x : a) {
        int a, b;
        cin >> a >> b;
        x = a - b;
    }
    sort(a.begin(), a.end());
    cout << (a[n / 2] - a[n / 2 - 1] + 1);
}