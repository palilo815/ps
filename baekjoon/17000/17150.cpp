#include <bits/stdc++.h>
using namespace std;

struct tile {
    int p, h;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<tile> b(n), f(n);
    for (auto& x : b) cin >> x.p;
    for (auto& x : b) cin >> x.h;
    for (auto& x : f) cin >> x.p;
    for (auto& x : f) cin >> x.h;

    vector<int> bdx(n), fdx(n);
    iota(bdx.begin(), bdx.end(), 0);
    iota(fdx.begin(), fdx.end(), 0);

    sort(bdx.begin(), bdx.end(), [&](auto& l, auto& r) {
        return b[l].p < b[r].p;
    });
    sort(fdx.begin(), fdx.end(), [&](auto& l, auto& r) {
        return f[l].p < f[r].p;
    });

    set<pair<int, int>> bset, fset;
    for (int i = 0, bi = 0, fi = 0; i < n;) {
        if (bset.empty())
            while (bi < n) {
                bset.emplace(b[bdx[bi]].h, bdx[bi]);
                if (++bi == n || b[bdx[bi - 1]].p != b[bdx[bi]].p) break;
            }
        if (fset.empty())
            while (fi < n) {
                fset.emplace(f[fdx[fi]].h, fdx[fi]);
                if (++fi == n || f[fdx[fi - 1]].p != f[fdx[fi]].p) break;
            }

        if (bset.size() < fset.size()) {
            for (const auto& x : bset) {
                auto it = fset.lower_bound({x.first, INT_MIN});
                if (it == fset.begin()) return cout << "impossible", 0;
                bdx[i] = x.second, fdx[i] = (--it)->second;
                ++i;
                fset.erase(it);
            }
            bset.clear();
        } else {
            for (const auto& x : fset) {
                auto it = bset.upper_bound({x.first, INT_MAX});
                if (it == bset.end()) return cout << "impossible", 0;
                fdx[i] = x.second, bdx[i] = it->second;
                ++i;
                bset.erase(it);
            }
            fset.clear();
        }
    }

    for (const auto& x : bdx) cout << x + 1 << ' ';
    cout << '\n';
    for (const auto& x : fdx) cout << x + 1 << ' ';
}