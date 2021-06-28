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

    string s;
    cin >> s;

    array<array<int, 9>, 9> cnt_move {};
    for (int i = 0; i < int(s.size()) - 1; ++i)
        ++cnt_move[s[i] - '1'][s[i + 1] - '1'];

    array<int, 9> pos;
    iota(pos.begin(), pos.end(), 0);

    int ans = INT_MAX;
    do {
        int sum = pos[s.front() - '1'];
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
                sum += cnt_move[i][j] * abs(pos[i] - pos[j]);
        chmin(ans, sum);
    } while (next_permutation(pos.begin(), pos.end()));
    cout << ans + s.size();
}