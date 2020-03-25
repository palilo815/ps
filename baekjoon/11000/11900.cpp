#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 2000;

int A[max_N];
int dist[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 1; i < N; ++i) cin >> A[i];

    fill(dist, dist + N, INT_MAX);
    dist[0] = 0;

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(0, 0);

    while (!pq.empty()) {
        auto [d, gap] = pq.top(); pq.pop();
        if (dist[gap] < d) continue;

        for (int GAP = 1; GAP < gap; ++GAP) if (A[N + GAP - gap]) {
            int D = d + A[N + GAP - gap];
            if (dist[GAP] > D) {
                dist[GAP] = D;
                pq.emplace(D, GAP);
            }
        }
        for (int GAP = gap + 1; GAP < N; ++GAP) if(A[GAP - gap]){
            int D = d + A[GAP - gap];
            if (dist[GAP] > D) {
                dist[GAP] = D;
                pq.emplace(D, GAP);
            }
        }
    }

    int Q; cin >> Q;
    while (Q--) {
        int u, v; cin >> u >> v;
        int d = (u > v ? dist[u - v] : dist[N - (v - u)]);
        cout << (d == INT_MAX ? -1 : d) << '\n';
    }
    return 0;
}