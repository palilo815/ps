#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int max_N = 100;

ll DP[max_N + 1];

int main() {
    int N; cin >> N;
    for (int i = 1; i <= N; ++i) DP[i] = i;
    for (int i = 1; i < N - 1; ++i) {
        ll buffer = DP[i];
        for (int j = i + 2; j <= N; ++j)
            DP[j] = max(DP[j], buffer * (j - i - 1));
    }
    cout << DP[N];
    return 0;
}