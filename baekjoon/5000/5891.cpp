#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, d;
    cin >> n >> d;

    vector<pair<int, int>> a(n);
    for (auto& [x, y] : a) cin >> x >> y;

    sort(a.begin(), a.end(), [&](auto& a, auto& b) {
        return a.first < b.first;
    });

    multiset<int> st;
    int ans = INT_MAX;
    for (int i = 0, j = 0; j < n;) {
        if (st.empty() || *st.rbegin() - *st.begin() < d)
            st.emplace(a[j++].second);
        else {
            ans = min(ans, a[j - 1].first - a[i].first);
            st.erase(st.find(a[i++].second));
        }
    }
    cout << (ans == INT_MAX ? -1 : ans);
}