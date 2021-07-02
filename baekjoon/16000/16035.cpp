#include <bits/stdc++.h>
using namespace std;

namespace std {
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template <class Fun>
class y_combinator_result {
    Fun fun_;

public:
    template <class T>
    explicit y_combinator_result(T&& fun) : fun_(std::forward<T>(fun)) {}

    template <class... Args>
    decltype(auto) operator()(Args&&... args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};

template <class Fun>
decltype(auto) y_combinator(Fun&& fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
}; // namespace std

constexpr int MX_N = 9;

bool played[MX_N][MX_N], win[MX_N][MX_N];
int score[MX_N], oppenent[MX_N][MX_N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

TOP:;
    int n, m;
    cin >> n;
    if (!n) return 0;
    cin >> m;

    memset(score, 0, sizeof(score));
    memset(played, 0, sizeof(played));
    for (int i = 0; i < n; ++i)
        played[i][i] = true;

    for (int u, v; m--;) {
        cin >> u >> v, --u, --v;
        played[u][v] = played[v][u] = true;
        ++score[u], --score[v];
    }

    int ans = 0;
    y_combinator([&](auto self, int u) -> void {
        if (u == n - 1) {
            ++ans;
            return;
        }

        int games = 0;
        for (int v = u + 1; v < n; ++v)
            if (!played[u][v])
                oppenent[u][games++] = v;

        if (games < abs(score[u])) return;

        const int need = (games - score[u]) / 2;
        memset(win[u], true, need);
        memset(win[u] + need, false, games - need);

        do {
            for (int i = 0; i < games; ++i) {
                int v = oppenent[u][i];
                win[u][i] ? --score[v] : ++score[v];
            }
            self(u + 1);
            for (int i = 0; i < games; ++i) {
                int v = oppenent[u][i];
                win[u][i] ? ++score[v] : --score[v];
            }
        } while (prev_permutation(win[u], win[u] + games));
    })(0);

    cout << ans << '\n';
    goto TOP;
}