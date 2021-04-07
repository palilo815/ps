#include <bits/stdc++.h>
using namespace std;

struct elem {
    int k, a, b;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    for (int n, A, B;;) {
        cin >> n >> A >> B;
        if (!n) break;

        vector<elem> vt(n);
        for (auto& [k, a, b] : vt)
            cin >> k >> a >> b;

        sort(vt.begin(), vt.end(), [&](auto& lhs, auto& rhs) {
            return lhs.a - lhs.b < rhs.a - rhs.b;
        });

        int ans = 0, mnA = -B;
        for (const auto& [k, a, b] : vt) {
            ans += k * b;
            mnA += k;
        }

        for (const auto& [k, a, b] : vt) {
            if (a > b && mnA <= 0) break;
            int from_A = min(k, a > b ? mnA : A);
            ans += from_A * (a - b);
            A -= from_A, mnA -= from_A;
        }
        cout << ans << '\n';
    }
}