#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

const int mxN = 1e3;

bool adj[26][26];
char s[mxN][mxN + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    char L;
    int N, M;
    cin >> L >> N;
    loop(i, N) cin >> s[i];
    M = L - 'a' + 1;

    loop(j, N) loop(i, j) for (int k = 0; s[i][k]; ++k) {
        if (!s[j][k]) {
            cout << "IMPOSSIBLE";
            return 0;
        } else if (s[i][k] ^ s[j][k]) {
            adj[s[i][k] - 'a'][s[j][k] - 'a'] = true;
            break;
        }
    }

    loop(k, M) loop(i, M) if (adj[i][k])
        loop(j, M) if (adj[k][j])
            adj[i][j] = true;

    loop(i, M) if (adj[i][i]) {
        cout << "IMPOSSIBLE";
        return 0;
    }

    vector<bool> done(M);
    string ans;
    for (;;) {
        int last = -1;
        loop(i, M) if (!done[i]) {
            bool flag = true;
            loop(j, M) if (adj[i][j]) {
                flag = false;
                break;
            }

            if (flag) {
                if (~last) {
                    cout << "AMBIGUOUS";
                    return 0;
                }
                last = i;
            }
        }
        if (last == -1) break;
        ans += (char)(last + 'a');
        done[last] = true;
        loop(i, 26) adj[i][last] = false;
    }
    reverse(ans.begin(), ans.end());
    cout << ans;
    return 0;
}