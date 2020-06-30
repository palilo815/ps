#include <bits/stdc++.h>
#define T(x) (x<<1)
#define F(x) (T(x)|1)
#define N(x) (x^1)
using namespace std;

struct _stick {
    int x1, y1, x2, y2;
};

const int M = 3000;
const pair<int, int> rest[3] = {{1, 2}, { -1, 1}, { -2, -1}};

_stick stick[M];

vector<int> adj[M << 1];
int t, scc_N;
int disc[M << 1], low[M << 1], scc[M << 1];
bool on_stack[M << 1];
stack<int> stk;

int ccw(int x1, int y1, int x2, int y2, int x3, int y3) {
    int ret = (x1 * y2 + x2 * y3 + x3 * y1) -
              (y1 * x2 + y2 * x3 + y3 * x1);
    if (ret > 0) return 1;
    else if (ret < 0) return -1;
    return 0;
}
int cross(_stick& a, _stick& b) {
    return ccw(a.x1, a.y1, a.x2, a.y2, b.x1, b.y1) != ccw(a.x1, a.y1, a.x2, a.y2, b.x2, b.y2) &&
           ccw(b.x1, b.y1, b.x2, b.y2, a.x1, a.y1) != ccw(b.x1, b.y1, b.x2, b.y2, a.x2, a.y2);
}
void dfs(int u) {
    disc[u] = low[u] = ++t;
    on_stack[u] = true;
    stk.emplace(u);

    for (int& v : adj[u]) {
        if (!disc[v]) dfs(v);
        if (on_stack[v]) low[u] = min(low[u], low[v]);
    }

    if (disc[u] == low[u]) {
        ++scc_N;
        while (1) {
            int x = stk.top(); stk.pop();
            on_stack[x] = false;
            scc[x] = scc_N;
            if (x == u) break;
        }
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    N *= 3;
    for (int i = 0; i < N; ++i) {
        auto& [x1, y1, x2, y2] = stick[i];
        cin >> x1 >> y1 >> x2 >> y2;
    }

    for (int a = 0; a < N; a += 3) {
        int b = a + 1, c = a + 2;
        adj[T(a)].emplace_back(F(b));
        adj[T(a)].emplace_back(F(c));
        adj[T(b)].emplace_back(F(c));
        adj[T(b)].emplace_back(F(a));
        adj[T(c)].emplace_back(F(a));
        adj[T(c)].emplace_back(F(b));
    }

    for (int i = 0; i < N - 1; ++i)
        for (int j = i + 1; j < N; ++j)
            if (cross(stick[i], stick[j])) {
                adj[F(i)].emplace_back(T(j));
                adj[F(j)].emplace_back(T(i));
            }

    for (int i = 0; i < N << 1; ++i)
        if (!disc[i])
            dfs(i);

    vector<int> ans;
    for (int i = 0; i < N << 1; i += 2) {
        if (scc[i] == scc[N(i)]) {
            ans.clear();
            break;
        }
        else if (scc[i] < scc[N(i)])
            ans.emplace_back((i >> 1) + 1);
    }

    cout << ans.size() << '\n';
    for (int& x : ans) cout << x << ' ';
    return 0;
}