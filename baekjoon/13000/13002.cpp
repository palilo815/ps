#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 2000;

int h[max_N];
int DP[max_N];
int tmp[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> h[i];

    // DP[i] : i, i+1, i+2, ... , i+N-day의 hay가 남았을 때 행복값
    for (int day = 1; day < N; ++day) {
        memset(tmp, 0, sizeof(int) * day);
        loop(i, day)
            tmp[i] = max(tmp[i], DP[i] + h[i + N - day] * day),
            tmp[i + 1] = max(tmp[i + 1], DP[i] + h[i] * day);
        memcpy(DP, tmp, sizeof(int) * (day + 1));
    }

    int ans = -1;
    loop(i, N) ans = max(ans, DP[i] + h[i] * N);
    cout << ans;
    return 0;
}