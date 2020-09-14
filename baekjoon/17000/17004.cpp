#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mxN = 1e5;

int nxt[mxN][26];
char s[mxN + 1], t[101];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> s >> t;
    int N = strlen(s);

    int pos[26];
    memset(pos, -1, sizeof(pos));

    for (int i = N - 1; ~i; --i) {
        move(pos, pos + 26, nxt[i]);
        pos[s[i] - 'a'] = i;
    }

    ll ans = 0;
    for (int i = 0; s[i]; ++i) {
        int k = i;
        for (int j = s[i] == t[0]; t[j]; ++j) {
            k = nxt[k][t[j] - 'a'];
            if (k == -1) break;
        }
        if (~k) ans += N - k;
    }
    cout << ans;
    return 0;
}