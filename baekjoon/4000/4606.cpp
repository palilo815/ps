#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

string Conv(char c)
{
    if (c == ' ') return "%20";
    else if (c == '!') return "%21";
    else if (c == '$') return "%24";
    else if (c == '%') return "%25";
    else if (c == '(') return "%28";
    else if (c == ')') return "%29";
    else if (c == '*') return "%2a";
    else return string(1, c);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    while (getline(cin, s)) {
        if (s == "#") break;
        loop(i, s.size())
            cout << Conv(s[i]);
        cout << '\n';
    }
    return 0;
}