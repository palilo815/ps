#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define T(x,i) ((psum[x]+i)<<1)
#define F(x,i) (T(x,i)|1)
#define N(x) (x^1)
using namespace std;

struct area {
    int x1, y1, x2, y2;
};

const int max_N = 300;
const int max_M = max_N * 15 * 2;
const string ans[2] = {"YES", "NO"};

vector<area> gang[max_N];
int psum[max_N + 1];

int t;
vector<int> adj[max_M];
int disc[max_M], low[max_M], scc[max_M];
bool on_stack[max_M];
stack<int> stk;

int overlap(area& A, area& B) {
    if (A.x2 <= B.x1 || B.x2 <= A.x1) return 0;
    if (A.y2 <= B.y1 || B.y2 <= A.y1) return 0;
    return 1;
}
void dfs(int u) {
    disc[u] = low[u] = ++t;
    on_stack[u] = true;
    stk.emplace(u);

    for (int& v : adj[u]) {
        if (!disc[v]) dfs(v);
        if (on_stack[v]) low[u] = min(low[u], low[v]);
    }

    if (disc[u] == low[u])
        while (1) {
            int x = stk.top(); stk.pop();
            on_stack[x] = false;
            scc[x] = low[u];
            if (x == u) break;
        }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) {
        int M; cin >> M;
        psum[i + 1] = psum[i] + M;
        gang[i].resize(M);
        for (auto& [x1, y1, x2, y2] : gang[i])
            cin >> x1 >> y1 >> x2 >> y2;

        loop(j, M) loop(k, M) if (j ^ k)
            adj[T(i, j)].emplace_back(F(i, k));

        for (auto& A : gang[i])
            loop(j, i) for (auto& B : gang[j])
                if (overlap(A, B)) {
                    adj[F(i, &A - &gang[i][0])].emplace_back(T(j, &B - &gang[j][0]));
                    adj[F(j, &B - &gang[j][0])].emplace_back(T(i, &A - &gang[i][0]));
                }
    }

    loop(i, psum[N] << 1) if (!disc[i])
        dfs(i);

    int flag = 0;
    for (int i = 0; i < psum[N] << 1; i += 2)
        if (scc[i] == scc[N(i)]) {
            flag = 1;
            break;
        }
    cout << ans[flag];
    return 0;
}