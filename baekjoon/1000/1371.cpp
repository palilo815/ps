#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int cnt[26];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    while (cin >> s) loop(i, s.size())
        ++cnt[s[i] - 'a'];
    int ans = 0;
    loop(i, 26) ans = max(ans, cnt[i]);
    loop(i, 26) if (cnt[i] == ans)
        cout << (char)(i + 'a');
    return 0;
}