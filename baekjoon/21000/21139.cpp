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

    char buf[11];

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (auto& x : a) {
        cin >> buf;
        for (int i = 0; i < k; ++i)
            x = x << 1 | (buf[i] == 'T');
    }

    int ans = 0;
    for (int mask = 0; mask < 1 << k; ++mask) {
        int score = INT_MAX;
        for (const auto& x : a)
            chmin(score, __builtin_popcount(x ^ mask));
        chmax(ans, score);
    }
    cout << ans;
}