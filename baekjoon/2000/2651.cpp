#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;

const int max_N = 100;
const int INF = 1 << 29;

int psum[max_N + 2];
int cost[max_N + 2];

int DP[max_N + 2];
int cache[max_N + 2];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T, N; cin >> T >> N;
    LOOP(i, N + 1) {
        int dist; cin >> dist;
        psum[i] = psum[i - 1] + dist;
    }
    LOOP(i, N) cin >> cost[i];

    LOOP(i, N + 1) {
        int tmp = INF;
        for (int j = i - 1; j >= 0 && psum[i] - psum[j] <= T; --j) {
            if (DP[j] + cost[i] < tmp) {
                tmp = DP[j] + cost[i];
                cache[i] = j;
            }
        }
        DP[i] = tmp;
    }

    vector<int> path;
    int u = cache[N + 1];
    while (u) {
        path.emplace_back(u);
        u = cache[u];
    }

    cout << DP[N + 1] << '\n' << path.size() << '\n';
    for (auto it = path.rbegin(); it != path.rend(); ++it)
        cout << *it << ' ';
    return 0;
}