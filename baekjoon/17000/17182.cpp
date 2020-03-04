#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef tuple<int, int, int> tup;

const int max_N = 10;

int w[max_N][max_N];
int dist[max_N][1 << max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, src; cin >> N >> src;
    loop(i, N) loop(j, N) cin >> w[i][j];
    loop(i, N) loop(j, 1 << N) dist[i][j] = INT_MAX;
    dist[src][1 << src] = 0;

    priority_queue<tup, vector<tup>, greater<tup>> pq;
    pq.emplace(0, 1 << src, src);
    while (1) {
        auto [d, visited, u] = pq.top(); pq.pop();
        if (dist[u][visited] < d) continue;
        if (visited == (1 << N) - 1) { cout << d; break; }
        
        loop(v, N) {
            int D = d + w[u][v];
            int mask = visited | (1 << v);
            if (dist[v][mask] > D) {
                dist[v][mask] = D;
                pq.emplace(D, mask, v);
            }
        }
    }
    return 0;
}