#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    vector<bool> erased(n);
    int ans = n;
    for (string s; m--;) {
        cin >> s;
        for (size_t it = 0, jt;; it = jt + 1) {
            jt = s.find(',', it);
            const auto word = s.substr(it, jt - it);
            if (auto id = lower_bound(a.begin(), a.end(), word); id != a.end() && *id == word) {
                if (!erased[id - a.begin()]) {
                    --ans;
                    erased[id - a.begin()] = true;
                }
            }
            if (jt == string::npos) {
                break;
            }
        }
        cout << ans << '\n';
    }
}