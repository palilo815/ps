#include <bits/stdc++.h>
using namespace std;

const int mxS = 1e6;
const int mxT = 1e5;

char s[mxS + 1], t[mxT + 1];
int dp[mxT][26];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> s >> t;

    int nxt[26];
    memset(nxt, -1, sizeof(nxt));

    for (int i = 0; t[i]; ++i)
        if (nxt[t[i] - 'a'] == -1)
            nxt[t[i] - 'a'] = i;

    for (int i = 0; s[i]; ++i)
        if (nxt[s[i] - 'a'] == -1)
            return cout << -1, 0;

    int start = nxt[s[0] - 'a'];
    for (int i = strlen(t) - 1; ~i; --i) {
        move(nxt, nxt + 26, dp[i]);
        nxt[t[i] - 'a'] = i;
    }

    int ans = 1;
    for (int i = 1, j = start; s[i]; ++i) {
        if (dp[j][s[i] - 'a'] <= j) ++ans;
        j = dp[j][s[i] - 'a'];
    }
    cout << ans;
}