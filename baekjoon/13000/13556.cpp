#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 100000;
const int mod = 5000000;

int N, K;
p arr[max_N];
int DP[max_N + 1];
int fenwick[max_N + 1];

void update(int i, int v) {
    while (i <= N) {
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

    cin >> N >> K;
    loop(i, N)
        cin >> arr[i].first,
        arr[i].second = i + 1;
    sort(arr, arr + N);

    DP[arr[0].second] = 1;
    for (int i = 1; i < N; ++i)
        if (arr[i].first != arr[i - 1].first)
            DP[arr[i].second] = 1;

    while (--K) {
        memset(fenwick, 0, sizeof(fenwick));
        loop(i, N) {
            int prv = 0;
            if (i && arr[i].first == arr[i - 1].first)
                prv = arr[i - 1].second;

            update(arr[i].second, DP[arr[i].second]);
            DP[arr[i].second] = (read(arr[i].second - 1) - read(prv) + mod) % mod;
        }
    }
    int ans = 0;
    for (int i = 1; i <= N; ++i) {
        ans += DP[i];
        ans %= mod;
    }
    cout << ans;
    return 0;
}