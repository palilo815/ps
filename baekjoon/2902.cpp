#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cin.tie(NULL);
    ios::sync_with_stdio(false);

    string s; getline(cin, s);
    cout << s[0];
    for (int i = 1; i < s.size(); ++i)
        if (s[i] == '-')
            cout << s[i + 1];
    return 0;
}