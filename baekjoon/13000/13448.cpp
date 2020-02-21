#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;

typedef struct {
    int M, P, R;
} info;

const int max_N = 50;
const int max_T = 100000;

info arr[max_N];
ll DP[max_T + 1];

bool cmp(const info& a, const info& b) {
    return (ll)a.R * b.P < (ll)b.R * a.P;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, T; cin >> N >> T;
    loop(i, N) cin >> arr[i].M;
    loop(i, N) cin >> arr[i].P;
    loop(i, N) cin >> arr[i].R;
    sort(arr, arr + N, cmp);

    loop(i, N) {
        auto [m, p, r] = arr[i];
        for (int t = T; t >= r; --t)
            DP[t] = max(DP[t], DP[t - r] + m - (ll)t * p);
    }

    ll ans = 0;
    loop(i, T + 1) ans = max(ans, DP[i]);
    cout << ans;
    return 0;
}