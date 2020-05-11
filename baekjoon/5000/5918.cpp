#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 5000;
const int max_M = 100000;

int cow[max_N];
int DP[max_N];
int price[max_M];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    loop(i, N) cin >> cow[i];
    loop(i, M) cin >> price[i];

    sort(cow, cow + N);
    int p_min = INT_MAX;
    for (int i = M - 1; i >= 0; --i) {
        p_min = min(p_min, price[i]);
        price[i] = p_min;
    }

    loop(i, N) DP[i] = price[cow[i] - cow[0]];
    for (int i = 1; i < N; ++i)
        for (int j = i; j < N; ++j)
            DP[j] = min(DP[j], DP[i - 1] + price[cow[j] - cow[i]]);
    cout << DP[N - 1];
    return 0;
}