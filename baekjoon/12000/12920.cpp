#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> p;

const int max_W = 10000;

ll DP[max_W + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    vector<p> item;
    int N, W; cin >> N >> W;
    while (N--) {
        int w, v, k; cin >> w >> v >> k;
        for (int i = 1; k; i *= 2) {
            int cnt = min(i, k);
            item.emplace_back(w * cnt, v * cnt);
            k -= cnt;
        }
    }
    
    memset(DP, -1, sizeof(DP));
    DP[0] = 0;

    for (auto [w, v] : item)
        for (int i = W - w; i >= 0; --i) {
            if (DP[i] == -1) continue;
            DP[i + w] = max(DP[i + w], DP[i] + v);
        }
    
    ll ans = 0;
    for (int i = 1; i <= W; ++i) ans = max(ans, DP[i]);
    cout << ans;
    return 0;
}