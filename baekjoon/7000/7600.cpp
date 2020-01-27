#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    bool T[26];
    while (getline(cin, s)) {
        if (s == "#") break;
        memset(T, 0, sizeof(T));
        int len = s.size();
        loop(i, len) {
            char c = s[i];
            if (c >= 'a' && c <= 'z') T[c - 'a'] = true;
            else if (c >= 'A' && c <= 'Z') T[c - 'A'] = true;
        }
        int ans = 0;
        loop(i, 26)
            if (T[i]) ++ans;
        cout << ans << '\n';
    }
    return 0;
}