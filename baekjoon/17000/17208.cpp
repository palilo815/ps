#include <bits/stdc++.h>
using namespace std;

const int MAX = 300;

int DP[MAX + 1][MAX + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    memset(DP, -1, sizeof(DP));
    DP[0][0] = 0;

    int N, A, B; cin >> N >> A >> B;
    while (N--) {
        int a, b; cin >> a >> b;
        for (int i = A - a; i >= 0; --i)
            for (int j = B - b; j >= 0; --j) {
                if (DP[i][j] == -1) continue;
                DP[i + a][j + b] = max(DP[i + a][j + b], DP[i][j] + 1);
            }
    }

    int ans = 0;
    for (int i = 0; i <= A; ++i) for (int j = 0; j <= B; ++j)
        ans = max(ans, DP[i][j]);
    cout << ans;
    return 0;
}