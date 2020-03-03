#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 300;

int cost[max_N][max_N];
bool water[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    priority_queue<p, vector<p>, greater<p>> pq;
    int N; cin >> N;
    loop(i, N) {
        int c; cin >> c;
        pq.push({ c,i });
    }
    loop(i, N) loop(j, N) cin >> cost[i][j];

    int ans = 0, cnt = N;
    while (cnt) {
        auto [c, u] = pq.top(); pq.pop();
        if (water[u]) continue;
        
        water[u] = true;
        ans += c;
        --cnt;

        loop(v, N) if (!water[v])
            pq.push({ cost[u][v], v });
    }
    cout << ans;
    return 0;
}