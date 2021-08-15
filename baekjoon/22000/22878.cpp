#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<int> p(n), q(n);
    for (auto& x : p) cin >> x;
    for (auto& x : q) cin >> x;
    vector<int> r(n), s(n);
    transform(p.begin(), p.end(), q.begin(), r.begin(), plus());
    transform(p.begin(), p.end(), q.begin(), s.begin(), minus());
    auto f = [&](vector<int>& v) {
        sort(v.begin(), v.end());
        int64_t ret = 0;
        for (int i = 0; i < n; ++i) {
            ret += int64_t(2 * i + 1 - n) * v[i];
        }
        return ret;
    };
    cout << 2 * (f(p) + f(q)) - (f(r) + f(s));
}