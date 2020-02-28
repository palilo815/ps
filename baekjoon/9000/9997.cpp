#include <bits/stdc++.h>
using namespace std;

const int max_N = 25;

int N;
int word[max_N];

int solve(int idx, int mask) {
    if (mask == (1 << 26) - 1) return pow(2, N - idx);
    if (idx == N) return 0;
    return solve(idx + 1, mask | word[idx]) + solve(idx + 1, mask);
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> N;
    string s;
    for (int i = 0; i < N; ++i) {
        cin >> s;
        int mask = 0;
        for (char c : s) mask |= 1 << (c - 'a');
        word[i] = mask;
    }
    cout << solve(0, 0);
    return 0;
}