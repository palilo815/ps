#include <bits/stdc++.h>
using namespace std;

const int max_K = 100000;

int DP[max_K + 1];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, K; cin >> N >> K;
    while (N--) {
        int a_t, a_won, b_t, b_won;
        cin >> a_t >> a_won >> b_t >> b_won;
        for (int i = K; i >= 0; --i) {
            DP[i] = INT_MIN;
            if (i >= a_t) DP[i] = max(DP[i], DP[i - a_t] + a_won);
            if (i >= b_t) DP[i] = max(DP[i], DP[i - b_t] + b_won);
        }
    }
    cout << DP[K];
    return 0;
}