#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 100000;

int money[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int N, M, K; cin >> N >> M >> K;
        loop(i, N) cin >> money[i];
        int sum = 0;
        loop(i, M) sum += money[i];

        if (N == M) { cout << (sum < K) << '\n'; continue; }

        int ans = 0, i = 0;
        while (i < N) {
            if (sum < K) ++ans;
            sum += money[(i + M) % N] - money[i];
            ++i;
        }
        cout << ans << '\n';
    }
    return 0;
}