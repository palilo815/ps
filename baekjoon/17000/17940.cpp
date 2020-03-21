#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 1000;
const int x = 1 << 20;

int adj[max_N][max_N];
bool line[max_N];
int dist[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, dst; cin >> N >> dst;
    loop(i, N) cin >> line[i];
    loop(i, N) loop(j, N) cin >> adj[i][j];

    fill(dist, dist + N, INT_MAX);

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(0, 0);

    while (1) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;
        if (u == dst) {
            cout << d / x << ' ' << d % x;
            break;
        }

        loop(v, N) if (adj[u][v]) {
            int D = d + adj[u][v] + (line[u] == line[v] ? 0 : x);
            if (dist[v] > D) {
                dist[v] = D;
                pq.emplace(D, v);
            }
        }
    }
    return 0;
}