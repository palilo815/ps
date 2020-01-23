#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int ASCII[26];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        loop(i, 26) ASCII[i] = 65 + i;
        string s; cin >> s;
        loop(i, s.size())
            ASCII[s[i] - 65] = 0;

        int ans = 0;
        loop(i, 26)
            ans += ASCII[i];
        cout << ans << '\n';
    }
    return 0;
}