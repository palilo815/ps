#include <bits/stdc++.h>

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

class BipartiteMatch {
    const std::vector<std::array<int, 2>>& adj;
    std::vector<int> match, rev;
    std::vector<int8_t> visited;

public:
    BipartiteMatch(int n, int m, const std::vector<std::array<int, 2>>& adj)
        : adj(adj), match(n, -1), rev(m, -1), visited(n) {}

    auto maximum_matching() {
        for (auto update = true; update;) {
            fill(visited.begin(), visited.end(), 0);
            update = false;
            for (auto i = 0; i < static_cast<int>(match.size()); ++i) {
                update |= match[i] == -1 && dfs(i);
            }
        }
        return match;
    }

private:
    auto dfs(int u) -> bool {
        visited[u] = 1;
        for (const auto& v : adj[u]) {
            if (rev[v] == -1 || (!visited[rev[v]] && dfs(rev[v]))) {
                match[u] = v, rev[v] = u;
                return true;
            }
        }
        return false;
    }
};

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<array<int, 2>> a(n);
    for (auto& [x, y] : a) {
        cin >> x >> y, --x, --y;
    }
    BipartiteMatch matcher(n, m, a);
    auto mat = matcher.maximum_matching();
    vector<int> get_first, get_second, poor;
    for (int i = 0; i < n; ++i) {
        if (mat[i] == a[i][0]) {
            get_first.emplace_back(i);
        } else if (mat[i] == a[i][1]) {
            get_second.emplace_back(i);
        } else if (mat[i] == -1) {
            poor.emplace_back(i);
        } else {
            assert(false);
        }
    }
    shuffle(get_second.begin(), get_second.end(), mt19937(random_device()()));
    vector<int8_t> taken(m);
    for (const auto& x : mat) {
        if (~x) {
            taken[x] = 1;
        }
    }
    for (;;) {
        const auto fence = remove_if(get_second.begin(), get_second.end(), [&](const auto& i) {
            if (!taken[a[i][0]]) {
                taken[a[i][0]] = 1;
                taken[a[i][1]] = 0;
                get_first.emplace_back(i);
                return true;
            }
            return false;
        });
        if (fence == get_second.end()) break;
        get_second.erase(fence, get_second.end());
    }
    vector taken_by(m, -1);
    for (const auto& i : get_second) {
        taken_by[a[i][1]] = i;
    }
    vector<int> free_cows;
    vector<vector<int>> next_cows(n);
    for (const auto& i : get_second) {
        if (~taken_by[a[i][0]]) {
            next_cows[taken_by[a[i][0]]].emplace_back(i);
        } else {
            free_cows.emplace_back(i);
        }
    }
    cout << poor.size() << '\n';
    for (const auto& x : get_first) cout << x + 1 << '\n';
    for (auto x : free_cows) {
        y_combinator([&](auto self, int u) -> void {
            cout << u + 1 << '\n';
            for (const auto& v : next_cows[u]) {
                self(v);
            }
        })(x);
    }
    for (const auto& x : poor) cout << x + 1 << '\n';
}
