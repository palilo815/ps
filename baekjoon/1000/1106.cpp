#include <bits/stdc++.h>
using namespace std;

const int max_C = 1100;
const int INF = 0x3f3f3f3f;

int DP[max_C];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    memset(DP, 0x3f, sizeof(DP));
    DP[0] = 0;

    int C, N; cin >> C >> N;
    while (N--) {
        int cost, val; cin >> cost >> val;
        for (int i = 0; i < C; ++i)
            if (DP[i] != INF)
                DP[i + val] = min(DP[i + val], DP[i] + cost);
    }
    cout << *min_element(DP + C, DP + C + 100);
    return 0;
}