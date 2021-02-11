#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, p, q, s;
    cin >> n >> p >> q >> s;

    vector<int> a(p), b(q);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    const int mx = max(a.back() - b.front(), b.back() - a.front());
    vector<int> stk;
    auto valid = [&](int diff) {
        stk.clear();
        int need = n;
        for (int i = p, j = 0; i--;) {
            while (j < q && a[i] + b[j] <= s) stk.emplace_back(b[j++]);
            while (!stk.empty() && stk.back() - a[i] > diff) stk.pop_back();
            if (!stk.empty() && a[i] - stk.back() <= diff) {
                if (--need == 0) return true;
                stk.pop_back();
            }
        }
        return false;
    };

    int lo = 0, hi = mx + 1;
    while (lo != hi) {
        int mid = (lo + hi) >> 1;
        valid(mid) ? hi = mid : lo = mid + 1;
    }
    cout << (lo == mx + 1 ? -1 : lo);
}