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
    constexpr int64_t INF = 0x3f3f3f3f3f3f3f3f;
    int n, k, lc, pc, lm, pm, t, d;
    cin >> n >> k >> lc >> pc >> lm >> pm >> t >> d;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    sort(a.begin(), a.end(), greater());
    vector<int64_t> need_c(n + 1), need_m(n + 1);
    vector<int64_t> free_c(n + 1), free_m(n + 1), free_p(n + 1);
    for (int i = 0; i < n; ++i) {
        if (a[i] < lc) {
            need_c[i + 1] = a[i] + d < lc ? INF : need_c[i] + lc - a[i];
        }
    }
    for (int i = 0; i < n; ++i) {
        if (a[i] < lm) {
            need_m[i + 1] = a[i] + d < lm ? INF : need_m[i] + lm - a[i];
        }
    }
    for (int i = 0; i < n; ++i) {
        free_c[i + 1] = free_c[i] + (a[i] > lc ? min(d, a[i] - lc) : 0);
    }
    for (int i = 0; i < n; ++i) {
        free_m[i + 1] = free_m[i] + (a[i] > lm ? min(d, a[i] - lm) : 0);
    }
    for (int i = 0; i < n; ++i) {
        free_p[i + 1] = free_p[i] + min(d, a[i] - 1);
    }
    int64_t ans = INF;
    for (int m = 0; m <= n; ++m) {
        const auto c = (n - m + k - 1) / k, p = n - m - c;
        // use m motors c cars, p passengers
        if (need_c[c] == INF || need_m[c + m] == INF) {
            continue;
        }
        const auto life_need = need_c[c] + need_m[c + m] - need_m[c];
        const auto life_free = free_c[c] + free_m[c + m] - free_m[c] + free_p[n] - free_p[c + m];
        if (life_need <= life_free) {
            chmin(ans, int64_t(pm) * m + int64_t(pc) * c + life_need * t);
        }
    }
    cout << (ans == INF ? -1 : ans);
}