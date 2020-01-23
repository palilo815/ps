#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

char Code[26];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        cin.ignore();
        string s; getline(cin, s);
        loop(i, 26) cin >> Code[i];
        int len = s.size();
        loop(i, len) {
            char c = s[i];
            if (c != ' ')
                c = Code[c - 'A'];
            cout << c;
        }
        cout << '\n';
    }
    return 0;
}