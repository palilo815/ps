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
    array<vector<int>, 26> indice;
    for (int i = 0; i < n; ++i) {
        indice[s[i] - 'a'].emplace_back(i);
    }
    for (auto& x : indice) {
        x.emplace_back(INT_MAX); // sentinel
    }
    int ans = 0;
    auto solve = [&](const vector<int>& most, const vector<int>& least) {
        if (most.size() == 1 || least.size() == 1) return;
        int res = INT_MIN, sum = 0;
        for (auto it = most.begin(), jt = least.begin(); *it != INT_MAX || *jt != INT_MAX;) {
            if (*it < *jt) {
                if (res != INT_MIN) chmax(ans, ++res);
                sum = sum < 0 ? 1 : sum + 1;
                ++it;
            } else {
                chmax(ans, res = sum - 1);
                sum = sum < 1 ? 0 : sum - 1;
                ++jt;
            }
        }
    };
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (i == j) continue;
            solve(indice[i], indice[j]);
        }
    }
    cout << ans;
}