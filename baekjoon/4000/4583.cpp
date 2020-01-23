#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)


int main()
{
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(false);

    string s;
    while (cin >> s) {
        if (s == "#") break;
        string ans = "";
        int pos = s.size() - 1;
        while (pos >= 0) {
            switch (s[pos--]) {
            case 'd':
                ans += 'b';
                break;
            case 'b':
                ans += 'd';
                break;
            case 'p':
                ans += 'q';
                break;
            case 'q':
                ans += 'p';
                break;
            case 'i':
            case 'o':
            case 'v':
            case 'w':
            case 'x':
                ans += s[pos + 1];
                break;
            default:
                ans = "INVALID";
                pos = -1;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}