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
    string s;
    cin >> n >> s;
    int64_t ans = 0, cur = 0;
    {
        // case 'I'
        int64_t j = 0, o = 0;
        for (const auto& c : s) {
            if (c == 'J') {
                ++j;
            } else if (c == 'O') {
                o += j;
            } else {
                cur += o;
            }
        }
        ans = cur + o;
    }
    {
        // case 'J'
        int64_t j = 1, o = 0, res = 0;
        for (const auto& c : s) {
            if (c == 'J') {
                ++j;
            } else if (c == 'O') {
                o += j;
            } else {
                res += o;
            }
        }
        chmax(ans, res);
    }
    {
        // case 'O'
        int64_t j = 0, i = count(s.begin(), s.end(), 'I');
        for (const auto& c : s) {
            if (c == 'J') {
                ++j;
            } else if (c == 'I') {
                --i;
            }
            chmax(ans, cur + j * i);
        }
    }
    cout << ans;
}