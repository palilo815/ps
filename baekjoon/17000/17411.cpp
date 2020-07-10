#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define x first
#define y second
#define L segT[i]
#define R segT[i^1]
using namespace std;
using p = pair<int, int>;

const int max_N = 1e6;
const int mod = 1e9 + 7;

int M, idx[max_N], arr[max_N << 1];
p dp[max_N], segT[max_N << 1];

void update(int i, p v) {
    if (segT[i].x > v.x) return;
    else if (segT[i].x == v.x) segT[i].y = (segT[i].y + v.y) % mod;
    else segT[i] = v;
    for (; i > 1; i >>= 1)
        segT[i >> 1] = L.x == R.x ? make_pair(L.x, (L.y + R.y) % mod) : (L.x > R.x ? L : R);
}
p query(int i) {
    p ret = {0, 0};
    for (int l = M, r = i + M; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            if (segT[l].x > ret.x) ret = segT[l];
            else if (segT[l].x == ret.x) ret.y = (ret.y + segT[l].y) % mod;
            ++l;
        }
        if (r & 1) {
            --r;
            if (segT[r].x > ret.x) ret = segT[r];
            else if (segT[r].x == ret.x) ret.y = (ret.y + segT[r].y) % mod;
        }
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> arr[i];

    copy(arr, arr + N, idx);
    sort(idx, idx + N);
    M = unique(idx, idx + N) - idx;

    loop(i, N) {
        int id = lower_bound(idx, idx + M, arr[i]) - idx;
        dp[i] = query(id);
        ++dp[i].x;
        if (!dp[i].y) ++dp[i].y;
        update(id + M, dp[i]);
    }

    int lis = 0, cnt = 0;
    loop(i, N) {
        if (dp[i].x > lis) lis = dp[i].x, cnt = dp[i].y;
        else if (dp[i].x == lis) cnt = (cnt + dp[i].y) % mod;
    }
    cout << lis << ' ' << cnt;
    return 0;
}