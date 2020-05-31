#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 100000;
const int mod = 5000000;

int arr[max_N];
int DP[max_N];
int fenwick[max_N + 1];

void update(int i, int v) {
    while (i <= max_N) {
        fenwick[i] += v;
        fenwick[i] %= mod;
        i += i & -i;
    }
}
int read(int i) {
    int ret = 0;
    while (i) {
        ret += fenwick[i];
        ret %= mod;
        i -= i & -i;
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, K; cin >> N >> K;
    loop(i, N) cin >> arr[i];

    fill(DP, DP + N, 1);
    while (--K) {
        memset(fenwick, 0, sizeof(fenwick));
        loop(i, N) {
            update(arr[i], DP[i]);
            DP[i] = read(arr[i] - 1);
        }
    }
    int ans = 0;
    loop(i, N) {
        ans += DP[i];
        ans %= mod;
    }
    cout << ans;
    return 0;
}