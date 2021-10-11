#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    string s;
    int n;
    cin >> s >> n;
    array<int, 26> s_cnt {}, t_cnt;
    for (const auto& x : s) {
        ++s_cnt[x - 'a'];
    }
    for (string t; n--;) {
        cin >> t;
        t_cnt.fill(0);
        if (s.size() < t.size()) {
            for_each(t.begin(), t.begin() + s.size(), [&](const auto& x) {
                ++t_cnt[x - 'a'];
            });
            int diff = 0;
            for (int i = 0; i < 26; ++i) {
                diff += abs(s_cnt[i] - t_cnt[i]);
            }
            if (diff < 3) {
                cout << "YES\n";
                continue;
            }
            bool yes = false;
            for (auto lt = t.begin(), rt = lt + s.size(); rt != t.end(); ++lt, ++rt) {
                --t_cnt[*lt - 'a'], ++t_cnt[*rt - 'a'];
                diff = 0;
                for (int i = 0; i < 26; ++i) {
                    diff += abs(s_cnt[i] - t_cnt[i]);
                }
                if (diff < 3) {
                    yes = true;
                    break;
                }
            }
            cout << (yes ? "YES\n" : "NO\n");
        } else if (s.size() > t.size()) {
            cout << "NO\n";
        } else {
            for (const auto& x : t) {
                ++t_cnt[x - 'a'];
            }
            int diff = 0;
            for (int i = 0; i < 26; ++i) {
                diff += abs(s_cnt[i] - t_cnt[i]);
            }
            cout << (diff == 2 ? "YES\n" : "NO\n");
        }
    }
}