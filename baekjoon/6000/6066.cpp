#include <bits/stdc++.h>
using namespace std;

const int max_C = 50000;
const int max_P = 5000;
const int INF = 0x3f3f3f3f;

int DP[max_C + max_P];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    memset(DP, 0x3f, sizeof(DP));
    DP[0] = 0;

    int N, H; cin >> N >> H;
    while (N--) {
        int p, c; cin >> p >> c;
        for (int i = 0; i < H; ++i)
            if (DP[i] != INF)
                DP[i + p] = min(DP[i + p], DP[i] + c);
    }
    cout << *min_element(DP + H, DP + H + max_P);
    return 0;
}