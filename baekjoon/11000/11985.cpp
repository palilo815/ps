#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int max_N = 20000;

int arr[max_N];
ll DP[max_N + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    memset(DP, 0x3f, sizeof(DP));
    DP[0] = 0;

    int N, M, K; cin >> N >> M >> K;
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
        int a = arr[i], b = arr[i];

        for (int j = i; j >= 0 && j > i - M; --j) {
            a = max(a, arr[j]), b = min(b, arr[j]);
            ll cost = K + (i - j + 1ll) * (a - b);
            DP[i + 1] = min(DP[i + 1], DP[j] + cost);
        }
    }
    cout << DP[N];
    return 0;
}