#include <bits/stdc++.h>
using namespace std;

struct edge {
    int u, v, w;
};

struct disjoint_set {
    vector<int> par;
    vector<pair<int, int>> stk;

    disjoint_set(int n) : par(n, -1) {}

    void clear() {
        fill(par.begin(), par.end(), -1);
    }
    int find(int u) {
        while (par[u] >= 0) u = par[u];
        return u;
    }
    int get_size(int u) {
        return -par[find(u)];
    }
    bool merge(int u, int v, bool record) {
        u = find(u), v = find(v);
        if (u == v) return false;

        if (par[u] > par[v]) swap(u, v);
        if (record) stk.emplace_back(v, par[v]);
        par[u] += par[v];
        par[v] = u;
        return true;
    }
    void roll_back() {
        for (; !stk.empty(); stk.pop_back()) {
            auto& [u, sz] = stk.back();
            par[par[u]] -= sz, par[u] = sz;
        }
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    vector<edge> e(m);
    for (auto& [u, v, w] : e)
        cin >> u >> v >> w, --u, --v;

    int q;
    cin >> q;

    vector<char> qtype(q);
    vector<pair<int, int>> query(q);
    for (int i = 0; i < q; ++i)
        cin >> qtype[i] >> query[i].first >> query[i].second, --query[i].first;

    const int BUCKET_SIZE = sqrt(m + q - 1) + 1;

    disjoint_set dsu(n);

    vector<bool> updated(m);
    vector<int> eid(m);
    iota(eid.begin(), eid.end(), 0);

    for (int l = 0; l < q; l += BUCKET_SIZE) {
        const int r = min(q, l + BUCKET_SIZE);

        dsu.clear();
        fill(updated.begin(), updated.end(), false);

        for (int i = l; i < r; ++i)
            if (qtype[i] == '1')
                updated[query[i].first] = true;

        // [0, pivot) = updated edge's id
        int pivot = partition(eid.begin(), eid.end(), [&](auto& x) {
            return updated[x];
        }) - eid.begin();

        vector<pair<int, vector<int>>> print_query;
        for (int i = l; i < r; ++i)
            if (qtype[i] == '1')
                e[query[i].first].w = query[i].second;
            else {
                vector<int> check_list;
                for (int j = 0; j < pivot; ++j)
                    if (e[eid[j]].w >= query[i].second)
                        check_list.emplace_back(eid[j]);
                print_query.emplace_back(i, check_list);
            }

        sort(eid.begin() + pivot, eid.end(), [&](auto& a, auto& b) {
            return e[a].w > e[b].w;
        });
        sort(print_query.begin(), print_query.end(), [&](auto& a, auto& b) {
            return query[a.first].second > query[b.first].second;
        });

        for (const auto& [qi, check_list] : print_query) {
            for (; pivot < m && e[eid[pivot]].w >= query[qi].second; ++pivot)
                dsu.merge(e[eid[pivot]].u, e[eid[pivot]].v, false);

            for (const auto& ei : check_list)
                dsu.merge(e[ei].u, e[ei].v, true);

            query[qi].first = dsu.get_size(query[qi].first);
            dsu.roll_back();
        }
    }

    for (int i = 0; i < q; ++i)
        if (qtype[i] == '2')
            cout << query[i].first << '\n';
}