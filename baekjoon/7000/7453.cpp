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
    vector<int> a(n), b(n), c(n), d(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
    }
    vector<int> ab(n * n), cd(n * n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ab[i * n + j] = a[i] + b[j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cd[i * n + j] = c[i] + d[j];
        }
    }
    sort(ab.begin(), ab.end());
    sort(cd.begin(), cd.end(), greater());
    auto it = ab.begin(), jt = cd.begin();
    int64_t ans = 0;
    for (;;) {
        if (*it + *jt < 0) {
            if (++it == ab.end()) {
                break;
            }
        } else if (*it + *jt > 0) {
            if (++jt == cd.end()) {
                break;
            }
        } else {
            const auto it2 = find_if(it, ab.end(), [&](const auto& x) { return x != *it; });
            const auto jt2 = find_if(jt, cd.end(), [&](const auto& x) { return x != *jt; });
            ans += (it2 - it) * (jt2 - jt);
            if (it2 == ab.end() || jt2 == cd.end()) break;
            it = it2, jt = jt2;
        }
    }
    cout << ans;
}