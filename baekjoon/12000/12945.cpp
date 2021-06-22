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
    for (auto& x : a) cin >> x;

    sort(a.begin(), a.end());

    int l = 0;
    for (int r = n >> 1; l < n >> 1 && r < n; ++r)
        if (a[l] << 1 <= a[r])
            ++l;
    cout << n - l << '\n';
}