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
    int ans = INT_MAX;
    for (int i = 0; i + 3 < n; ++i) {
        for (int j = i + 3; j < n; ++j) {
            const int s0 = a[i] + a[j];
            for (int it = i + 1, jt = j - 1; it != jt;) {
                const int s1 = a[it] + a[jt];
                chmin(ans, abs(s0 - s1));
                s0 < s1 ? --jt : ++it;
            }
        }
    }
    cout << ans;
}