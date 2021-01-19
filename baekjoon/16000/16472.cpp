#include <bits/stdc++.h>
using namespace std;

const int mxS = 1e5;

char s[mxS + 1];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n >> s;

    int ans = 0, cnt[26] {};
    for (int i = 0, j = 0, use = 0; s[j];) {
        for (; s[j] && use <= n; ++j)
            use += ++cnt[s[j] - 'a'] == 1;
        for (ans = max(ans, j - i - (use > n)); use > n; ++i)
            use -= --cnt[s[i] - 'a'] == 0;
    }
    cout << ans;
}