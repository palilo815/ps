#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace std;

template <typename flow_t, typename cost_t>
class MCMF_SSPA {
    struct edge_t {
        int dest;
        flow_t cap;
        cost_t cost;
        edge_t(int _dest, flow_t _cap, cost_t _cost) : dest(_dest), cap(_cap), cost(_cost) {}
    };

    const cost_t INF_COST = cost_t(0x3f3f3f3f3f3f3f3f);
    const flow_t INF_FLOW = flow_t(0x3f3f3f3f3f3f3f3f);

    const int n;
    vector<vector<int>> adj;
    vector<edge_t> edges;
    vector<char> seen;
    vector<cost_t> pi;
    vector<int> prv;

public:
    MCMF_SSPA(int _n) : n(_n), adj(n), pi(n), prv(n) {}

    void add_edge(int u, int v, flow_t cap, cost_t cost) {
        assert(cap >= 0 and cost >= 0);
        int e = edges.size();
        edges.emplace_back(v, cap, cost);
        edges.emplace_back(u, 0, -cost);
        adj[u].push_back(e);
        adj[v].push_back(e + 1);
    }
    pair<flow_t, cost_t> maxflow(int s, int t) {
        assert(s != t);
        flow_t tot_flow = 0;
        cost_t tot_cost = 0;

        while (path(s), pi[t] < INF_COST) {
            flow_t flow = numeric_limits<flow_t>::max();
            for (int cur = t; cur != s;) {
                int e = prv[cur];
                flow = min(flow, edges[e].cap);
                cur = edges[e ^ 1].dest;
            }

            tot_flow += flow;
            tot_cost += pi[t] * flow;

            for (int cur = t; cur != s;) {
                int e = prv[cur];
                edges[e].cap -= flow;
                edges[e ^ 1].cap += flow;
                cur = edges[e ^ 1].dest;
            }
        }
        return {tot_flow, tot_cost};
    }

private:
    vector<cost_t> dist;
    __gnu_pbds::priority_queue<pair<cost_t, int>> pq;
    vector<typename decltype(pq)::point_iterator> its;

    void path(int s) {
        dist.assign(n, INF_COST);
        dist[s] = 0;

        its.assign(n, pq.end());
        its[s] = pq.push({0, s});

        while (!pq.empty()) {
            const auto i = pq.top().second;
            pq.pop();

            cost_t d = dist[i];
            for (const auto& e : adj[i]) {
                if (edges[e].cap) {
                    int j = edges[e].dest;
                    cost_t nd = d + edges[e].cost;
                    if (nd < dist[j]) {
                        dist[j] = nd;
                        prv[j] = e;
                        if (its[j] == pq.end())
                            its[j] = pq.push({pi[j] - dist[j], j});
                        else
                            pq.modify(its[j], {pi[j] - dist[j], j});
                    }
                }
            }
        }
        swap(pi, dist);
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    // [1, n]  [n + 1, n + m]
    const int s = 0, t = n + m + 1;
    MCMF_SSPA<int, int> mcmf(t + 1);

    for (int i = 1, x, job, cost; i <= n; ++i)
        for (cin >> x; x--;) {
            cin >> job >> cost;
            mcmf.add_edge(i, n + job, 1, cost);
        }

    for (int i = 1; i <= n; ++i)
        mcmf.add_edge(s, i, 1, 0);
    for (int i = n + 1; i <= n + m; ++i)
        mcmf.add_edge(i, t, 1, 0);

    auto res = mcmf.maxflow(s, t);
    cout << res.first << '\n'
         << res.second;
}