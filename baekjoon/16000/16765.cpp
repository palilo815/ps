#include <bits/stdc++.h>
#define REP(i,s,e) for(int i=s;i<=e;++i)
using namespace std;

const int max_N = 10001;

int S[max_N];
int DP[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, K; cin >> N >> K;
    REP(i, 1, N) cin >> S[i];

    REP(i, 1, N) {
        int best = 0, e = min(i + K - 1, N);
        REP(j, i, e) {
            best = max(best, S[j]);
            DP[j] = max(DP[j], DP[i - 1] + best * (j - i + 1));
        }
    }
    cout << DP[N];
    return 0;
}