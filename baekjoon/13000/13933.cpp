#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<int> a(n), b(n);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;

    unordered_set<int> st;
    for (const auto& x : a)
        st.count(x) ? void(st.erase(x)) : void(st.emplace(x));

    int ans = 0;
    if (!st.empty()) ans = *max_element(st.begin(), st.end());

    auto valid = [&](int mid) {
        int prv = -1;
        for (auto& vt : {a, b})
            for (auto& x : vt) {
                if (x <= mid) continue;
                if (prv == -1) prv = x;
                else {
                    if (prv != x) return false;
                    prv = -1;
                }
            }
        return true;
    };

    int lo = ans, hi = 1e9;
    while (lo != hi) {
        const auto mid = lo + hi >> 1;
        valid(mid) ? hi = mid : lo = mid + 1;
    }
    cout << lo;
}