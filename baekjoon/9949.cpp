#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    char c1, c2;
    int T = 0, n;
    while (cin >> c1 >> c2) {
        if (c1 == '#') break;
        cin >> n; cin.ignore();
        cout << "Case " << ++T << '\n';
        while (n-- > 0) {
            getline(cin, s);
            int Len = s.length();
            loop(i, Len) {
                if (s[i] == c1 || s[i] == c2 || s[i] == c1 - 'a' + 'A' || s[i] == c2 - 'a' + 'A') cout << '_';
                else cout << s[i];
            }
            cout << '\n';
        }
        cout << '\n';
    }
    return 0;
}