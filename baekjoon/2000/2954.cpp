#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

char mo[5] = { 'a','e','i','o','u' };
bool mouem(char c)
{
    loop(i, 5)
        if (c == mo[i]) return true;
    return false;
}
int main()
{
    cin.tie(NULL), cin.tie(NULL);
    ios::sync_with_stdio(false);

    string s; getline(cin, s);
    loop(i, s.size()) {
        cout << s[i];
        if (mouem(s[i])) i += 2;
    }
    return 0;
}