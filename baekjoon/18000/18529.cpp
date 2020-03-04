#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 50;
const int max_K = 2500;

vector<p> tile[max_K + 1];
int dist[max_N][max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, K; cin >> N >> K;
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
        int x; cin >> x;
        tile[x].emplace_back(i, j);
    }

    fill(&dist[0][0], &dist[N][0], INT_MAX);
    priority_queue<p, vector<p>, greater<p>> pq;
    for (auto [r, c] : tile[1]) {
        dist[r][c] = 0;
        pq.emplace(0, 64 * 64 + r * 64 + c);
    }

    while (!pq.empty()) {
        auto [d, num] = pq.top(); pq.pop();
        int c = num % 64; num /= 64;
        int r = num % 64; num /= 64;
        if (dist[r][c] < d) continue;
        if (num == K) { cout << d; return 0; }

        for (auto [R, C] : tile[num + 1]) {
            int D = d + abs(R - r) + abs(C - c);
            if (dist[R][C] > D) {
                dist[R][C] = D;
                pq.emplace(D, (num + 1) * 64 * 64 + R * 64 + C);
            }
        }
    }
    cout << -1;
    return 0;
}