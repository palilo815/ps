#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

char T[5] = { 'a', 'e', 'i', 'o', 'u' };
bool Mo(char c)
{
    loop(i, 5) if (c == T[i]) return true;
    return false;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    while (1) {
        cin >> s;
        if (s == "#") break;
        int pos = 0, len = s.size();
        while (!Mo(s[pos]) && pos < len) ++pos;
        for (int i = pos; i < len; ++i) cout << s[i];
        loop(i, pos) cout << s[i];
        cout << "ay\n";
    }
    return 0;
}