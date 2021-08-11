#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

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
    int abs_min = INT_MAX;
    pair best(0, 0);
    for (int i = 0, j = n - 1; i < j;) {
        if (chmin(abs_min, abs(a[i] + a[j]))) {
            best = {a[i], a[j]};
        }
        a[i] + a[j] < 0 ? ++i : --j;
    }
    cout << best.first << ' ' << best.second;
}