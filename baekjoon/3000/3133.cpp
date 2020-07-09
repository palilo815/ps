#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define x first
#define y second
#define L segT[i]
#define R segT[i^1]
using namespace std;
using p = pair<int, int>;

const int max_N = 3e5;
const int mod = 1000000007;

int M;
p dp[max_N];
p arr[max_N << 1];
int id[max_N];
vector<p> segT;

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
    loop(i, N) cin >> arr[i].x >> arr[i].y;

    loop(i, N) id[i] = arr[i].y;
    sort(id, id + N);
    M = unique(id, id + N) - id;
    segT.resize(M << 1);

    sort(arr, arr + N, [&](p & a, p & b) -> bool {
        return a.x == b.x ? a.y > b.y : a.x < b.x;
    });

    loop(i, N) {
        int y = lower_bound(id, id + M, arr[i].y) - id;
        dp[i] = query(y);
        ++dp[i].x;
        if (dp[i].y == 0) dp[i].y = 1;
        update(y + M, dp[i]);
    }

    int jump = 0, cnt = 0;
    loop(i, N) {
        if (dp[i].x > jump) jump = dp[i].x, cnt = dp[i].y;
        else if (dp[i].x == jump) cnt = (cnt + dp[i].y) % mod;
    }
    cout << jump << '\n' << cnt;
    return 0;
}