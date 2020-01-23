#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    int pos[26];
    memset(pos, -1, sizeof(pos));
    string s; cin >> s;
    loop(i, s.size())
        if (pos[s[i] - 'a'] == -1)
            pos[s[i] - 'a'] = i;
    loop(i, 26) cout << pos[i] << ' ';
    return 0;
}