#include <iostream>
using namespace std;

const int max_g = 200000;

int DP[max_g * 13 + 1];

int main() {
    int N; cin >> N;
    DP[0] = 1;
    int sum = 0;
    for (int i = 1; i <= N; ++i) {
        int x; cin >> x;
        for (int g = 0; g <= sum; ++g)
            if (DP[g] == i) {
                if (DP[g + x] != i) DP[g + x] = i + 1;
                if (DP[abs(g - x)] != i) DP[abs(g - x)] = i + 1;
                DP[g] = i + 1;
            }
        sum += x;
    }

    int ans = 0;
    for (int i = 0; i <= sum; ++i)
        if (!DP[i]) ++ans;
    cout << ans;
    return 0;
}