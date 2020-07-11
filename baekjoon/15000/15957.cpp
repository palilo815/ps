#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using ll = long long;
struct query {
    int t, p, s;
};

const int MAX = 1e5;

int t, N;
vector<int> adj[MAX], song[MAX];
int singer[MAX], in[MAX], out[MAX];
int lo[MAX], hi[MAX];
ll fenwick[MAX + 1];
query q[MAX];

void update(int i, int v) {
    for (; i <= N; i += i & -i)
        fenwick[i] += v;
}
ll read(int i) {
    ll ret = 0;
    for (; i; i -= i & -i)
        ret += fenwick[i];
    return ret;
}
void dfs(int u) {
    in[u] = ++t;
    for (int& v : adj[u])
        dfs(v);
    out[u] = t;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int M, K; cin >> N >> M >> K;
    for (int v = 1, u; v < N; ++v) {
        cin >> u;
        adj[u - 1].emplace_back(v);
    }
    loop(i, N) {
        cin >> singer[i];
        song[--singer[i]].emplace_back(i);
    }

    dfs(0);

    loop(i, M) {
        cin >> q[i].t >> q[i].p >> q[i].s;
        --q[i].p;
    }
    sort(q, q + M, [&](auto & a, auto & b) -> bool {
        return a.t < b.t;
    });

    loop(i, N) if (song[i].empty())
        lo[i] = M;
    fill(hi, hi + N, M);

    while (1) {
        memset(fenwick + 1, 0, sizeof(ll) * N);
        vector<vector<int>> vt(M);

        bool done = true;
        loop(i, N) if (lo[i] ^ hi[i]) {
            vt[(lo[i] + hi[i]) >> 1].emplace_back(i);
            done = false;
        }
        if (done) break;

        loop(m, M) {
            int i = in[q[m].p], o = out[q[m].p];
            int val = q[m].s / (o - i + 1);
            update(i, val), update(o + 1, -val);

            for (int& i : vt[m]) {
                ll total = 0;
                for (int& s : song[i])
                    total += read(in[s]);
                total <= song[i].size() * K ? (lo[i] = m + 1) : (hi[i] = m);
            }
        }
    }

    loop(i, N) {
        int s = singer[i];
        cout << (lo[s] == M ? -1 : q[lo[s]].t) << '\n';
    }
    return 0;
}