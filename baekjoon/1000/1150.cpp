#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<int> dist(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        dist[i] = a[i + 1] - a[i];
    }
    set<pair<int, int>> st;
    for (int i = 0; i < n - 1; ++i) {
        st.emplace(dist[i], i);
    }
    vector<int> lhs(n), rhs(n);
    iota(lhs.begin(), lhs.end(), -1);
    iota(rhs.begin(), rhs.end(), 1);
    rhs.back() = -1;
    int ans = 0;
    while (k--) {
        const auto [d, l] = *st.begin();
        st.erase(st.begin());
        ans += d;
        const bool erase_lhs = lhs[l] != -1 && st.erase(pair(dist[lhs[l]], lhs[l]));
        const bool erase_rhs = rhs[rhs[l]] != -1 && st.erase(pair(dist[rhs[l]], rhs[l]));
        if (erase_lhs && erase_rhs) {
            st.emplace(dist[lhs[l]] = dist[lhs[l]] + dist[rhs[l]] - dist[l], lhs[l]);
            rhs[lhs[l]] = rhs[rhs[l]];
            lhs[rhs[rhs[l]]] = lhs[l];
        }
    }
    cout << ans;
}