#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 1000;

int adj[max_N][max_N];
int happy[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) loop(j, N) cin >> adj[i][j];
    fill(happy, happy + N, INT_MIN);

    priority_queue<p> pq;
    int src, dst; cin >> src >> dst;
    while (src--) {
        int idx, val; cin >> idx >> val;
        --idx;
        happy[idx] = val;
        pq.emplace(val, idx);
    }

    vector<p> vt(dst);
    loop(i, dst) cin >> vt[i].first >> vt[i].second;

    while (!pq.empty()) {
        auto [h, u] = pq.top(); pq.pop();
        if (happy[u] > h) continue;

        loop(v, N) if (adj[u][v]) {
            int H = h - adj[u][v];
            if (happy[v] < H) {
                happy[v] = H;
                pq.emplace(H, v);
            }
        }
    }

    int ans = INT_MIN;
    for (auto [idx, val] : vt)
        ans = max(ans, happy[idx - 1] + val);
    cout << ans;
    return 0;
}