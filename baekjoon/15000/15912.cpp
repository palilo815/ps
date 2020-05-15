#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;

const int max_N = 1000;

int w[max_N];
int e[max_N];
ll DP[max_N + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> w[i];
    loop(i, N) cin >> e[i];

    memset(DP + 1, 0x3f, sizeof(ll) * N);
    // DP[i] : i번 이전의 모든 부품을 사는 최소비용

    loop(i, N) {
        int w_max = 0, e_max = 0;
        for (int j = i; j < N; ++j) {
            w_max = max(w_max, w[j]), e_max = max(e_max, e[j]);
            DP[j + 1] = min(DP[j + 1], DP[i] + (ll)w_max * e_max);
        }
    }
    cout << DP[N];
    return 0;
}