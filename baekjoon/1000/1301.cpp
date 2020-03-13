#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;

int N, cnt[5];
ll DP[11][11][11][11][11][5][5];

ll top_down(int use1, int use2) {
    ll& ret = DP[cnt[0]][cnt[1]][cnt[2]][cnt[3]][cnt[4]][use1][use2];
    if (ret != -1) return ret;
    if (cnt[0] + cnt[1] + cnt[2] + cnt[3] + cnt[4] == 0) return ret = 1;
    
    ret = 0;
    loop(i, N) if (cnt[i] && i != use1 && i != use2) {
        --cnt[i];
        ret += top_down(use2, i);
        ++cnt[i];
    }
    return ret;
}
int main() {
    memset(DP, -1, sizeof(DP));
    cin >> N;
    loop(i, N) cin >> cnt[i];

    ll ans = 0;
    loop(i, N) loop(j, N) if (i != j) {
        --cnt[i], --cnt[j];
        ans += top_down(i, j);
        ++cnt[i], ++cnt[j];
    }
    cout << ans;
    return 0;
}