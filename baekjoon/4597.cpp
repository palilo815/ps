#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    while (cin >> s) {
        if (s == "#") break;
        int L = s.size(), cnt = 0;
        loop(i, L - 1)
            if (s[i] == '1') ++cnt;
        if (s[L - 1] == 'o') {
            if (cnt % 2) s[L - 1] = '0';
            else s[L - 1] = '1';
        }
        else {
            if (cnt % 2) s[L - 1] = '1';
            else s[L - 1] = '0';
        }
        cout << s << '\n';
    }
    return 0;
}