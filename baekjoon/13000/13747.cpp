#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;
typedef pair<ll, ll> p;

const int max_K = 200000;

p arr[max_K];
ll DP[max_K + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    ll N; cin >> N;
    int K; cin >> K;
    loop(i, K) cin >> arr[i].first >> arr[i].second;
    sort(arr, arr + K);

    loop(i, K) {
        auto [l, r] = arr[i];
        DP[i + 1] = max(DP[i + 1], DP[i]);
        auto nxt = lower_bound(arr + i + 1, arr + K, make_pair(r + 1, 0ll)) - arr;
        DP[nxt] = max(DP[nxt], DP[i] + r - l + 1);
    }
    cout << N - DP[K];
    return 0;
}