#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

bool have[4][13];
int conv(char c)
{
    switch (c) {
    case 'P':return 0;
    case 'K': return 1;
    case 'H': return 2;
    case 'T': return 3;
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s; cin >> s;
    int len = s.size() / 3;
    loop(i, len) {
        int mark = conv(s[3 * i]);
        int num = (s[3 * i + 1] - '0') * 10 + s[3 * i + 2] - '0' - 1;
        if (have[mark][num]) {
            cout << "GRESKA";
            return 0;
        }
        have[mark][num] = true;
    }
    loop(i, 4) {
        int x = 0;
        loop(j, 13)
            if (!have[i][j]) ++x;
        cout << x << ' ';
    }
    return 0;
}