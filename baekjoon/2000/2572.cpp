#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 1000;
const int max_V = 500;

int DP[2][max_N];
char card[max_N];
vector<int> red[max_V + 1];
vector<int> green[max_V + 1];
vector<int> blue[max_V + 1];
int src, dst, V;

void solve(vector<int>* vt, int score) {
    for (int u = 1; u <= V; ++u) {
        if (DP[src][u] == -1) continue;
        for (int v : vt[u])
            DP[dst][v] = max(DP[dst][v], DP[src][u] + score);
    }
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, E; cin >> N;
    loop(i, N) cin >> card[i];
    cin >> V >> E;
    while (E--) {
        int u, v; char c;
        cin >> u >> v >> c;
        vector<int>* vt;
        if (c == 'R') vt = red;
        else if (c == 'G') vt = green;
        else vt = blue;
        vt[u].push_back(v);
        vt[v].push_back(u);
    }

    memset(DP[0], -1, max_N);
    DP[0][1] = 0;
    loop(i, N) {
        char c = card[i];
        src = i % 2, dst = 1 - (i % 2);
        memset(DP[dst], -1, max_N);
        switch (c) {
        case 'R':
            solve(green, 0), solve(blue, 0), solve(red, 10);
            break;
        case 'G':
            solve(blue, 0), solve(red, 0), solve(green, 10);
            break;
        default:
            solve(red, 0), solve(green, 0), solve(blue, 10);
        }
    }
    
    int cur = N % 2, ans = 0;
    for (int i = 1; i <= V; ++i) ans = max(ans, DP[cur][i]);
    cout << ans;
    return 0;
}