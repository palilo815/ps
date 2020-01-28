#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int d, m, y;
    string s;
    while (cin >> d >> m >> y) {
        y += d + m;
        if (y == 0) break;
        int Sh = (y % 25) + 1;
        cin.ignore();
        getline(cin, s);
        int len = s.size();
        loop(i, len) {
            char c = s[i];
            if (c >= 'a' && c <= 'z') { c -= Sh; if (c < 'a') c += 26; }
            cout << c;
        }
        cout << '\n';
    }
    return 0;
}