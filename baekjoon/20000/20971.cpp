#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, q;
    string s;
    cin >> n >> q >> s;

    array<int, 26> pos;

    // dp_f[i] =  # of strokes to paint [0, i)
    vector<int> dp_f(n + 1);
    fill(pos.begin(), pos.end(), -1);
    for (int i = 0; i < n; ++i) {
        int cur = s[i] - 'A';
        dp_f[i + 1] = dp_f[i] + (pos[cur] == -1 || any_of(pos.begin(), pos.begin() + cur, [&](auto& x) { return pos[cur] < x; }));
        pos[cur] = i;
    }

    // dp_b[i] =  # of strokes to paint [i, n)
    vector<int> dp_b(n + 1);
    fill(pos.begin(), pos.end(), n);
    for (int i = n; i--;) {
        int cur = s[i] - 'A';
        dp_b[i] = dp_b[i + 1] + (pos[cur] == n || any_of(pos.begin(), pos.begin() + cur, [&](auto& x) { return x < pos[cur]; }));
        pos[cur] = i;
    }

    vector<int> ans(q);
    for (int l, r, i = 0; i < q; ++i) {
        cin >> l >> r, --l;
        cout << dp_f[l] + dp_b[r] << '\n';
    }
}