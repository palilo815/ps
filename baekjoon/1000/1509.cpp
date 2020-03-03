#include <bits/stdc++.h>
using namespace std;

const int max_N = 2500;

string s;
int DP[max_N + 1];

bool pallin(int l, int r) {
    while (l < r) if (s[l++] != s[r--]) return false;
    return true;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> s;
    int N = s.size();

    fill(DP + 1, DP + N + 1, INT_MAX);
    DP[0] = 0;

    for (int i = 1; i <= N; ++i) for (int j = i; j <= N; ++j)
        if (pallin(i - 1, j - 1))
            DP[j] = min(DP[j], DP[i - 1] + 1);
    cout << DP[N];
    return 0;
}