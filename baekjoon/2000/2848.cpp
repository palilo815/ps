#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 100;

char s[mxN][11];
bool use[26];
bool adj[26][26];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> s[i];
    loop(i, N) for (int j = 0; s[i][j]; ++j)
        use[s[i][j] - 'a'] = true;

    loop(i, N - 1) for (int j = i + 1; j < N; ++j)
        for (int k = 0; s[i][k]; ++k)
            if (!s[j][k]) {cout << '!'; return 0;}
            else if (s[i][k] ^ s[j][k]) {
                adj[s[i][k] - 'a'][s[j][k] - 'a'] = true;
                break;
            }

    loop(k, 26) loop(i, 26) if (adj[i][k])
        loop(j, 26) if (adj[k][j])
            adj[i][j] = true;

    loop(i, 26) if (adj[i][i]) {cout << '!'; return 0;}

    string ans;
    for (;;) {
        int last = -1;
        loop(i, 26) if (use[i]) {
            bool flag = true;
            loop(j, 26) if (adj[i][j]) {
                flag = false;
                break;
            }

            if (flag) {
                if (~last) {cout << '?'; return 0;}
                last = i;
            }
        }
        if (last == -1) break;
        ans += (char)(last + 'a');
        use[last] = false;
        loop(i, 26) adj[i][last] = false;
    }
    reverse(ans.begin(), ans.end());
    cout << ans;
    return 0;
}