#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef tuple<int, int, int> tup;

const int max_N = 300000;

tup arr[max_N];
int DP[max_N + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) {
        auto& [s, e, c] = arr[i];
        cin >> s >> e >> c;
    }
    sort(arr, arr + N);

    loop(i, N) {
        auto& [s, e, c] = arr[i];
        DP[i + 1] = max(DP[i + 1], DP[i]);

        auto nxt = lower_bound(arr + i + 1, arr + N, make_tuple(e + 1, 0, 0)) - arr;
        DP[nxt] = max(DP[nxt], DP[i] + c);
    }
    cout << DP[N];
    return 0;
}