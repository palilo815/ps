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

    int ans = INT_MAX;
    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 1; j < n; ++j)
            chmin(ans, accumulate(a.begin(), a.end(), 0, [&](auto& sum, auto& x) {
                return sum + min((a[i] - x) * (a[i] - x), (a[j] - x) * (a[j] - x));
            }));
    cout << ans;
}