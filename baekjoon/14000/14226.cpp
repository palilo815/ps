#include <bits/stdc++.h>
using namespace std;

const int MAX = 1100;

int DP[MAX + 1];

int main() {
    fill(DP, DP + MAX + 1, INT_MAX / 2);
    DP[1] = 0;

    int N; cin >> N;
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= MAX; ++j)
            DP[i] = min(DP[i], DP[j] + j - i);
        int cost = 2;
        for (int j = i * 2; j <= MAX; j += i)
            DP[j] = min(DP[j], DP[i] + cost++);
    }
    cout << DP[N];
    return 0;
}