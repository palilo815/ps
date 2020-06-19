#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using p = pair<int, int>;

const int M = 10000;

p arr[M];
int DP[M + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> arr[i].first >> arr[i].second;
    sort(arr, arr + N);

    memset(DP + 1, 0x3f, sizeof(int) * N);
    loop(i, N) {
        int y_min = 1000000, y_max = -1000000;
        for (int j = i; j < N; ++j) {
            y_min = min(y_min, arr[j].second);
            y_max = max(y_max, arr[j].second);
            DP[j + 1] = min(DP[j + 1], DP[i] + max(arr[j].first - arr[i].first, 2 * max(y_max, -y_min)));
        }
    }
    cout << DP[N];
    return 0;
}