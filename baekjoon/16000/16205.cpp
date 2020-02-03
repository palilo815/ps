#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

void conv(string& s, int u, int v)
{
    if (u == v) {
        cout << s;
        return;
    }

    int len = s.size();
    switch (u) {
    case 1:
        if (v == 2)
            loop(i, len) {
            if (s[i] < 'a')
                cout << '_' << char(s[i] + 32);
            else cout << s[i];
        }
        if (v == 3) {
            s[0] -= 32;
            cout << s;
            s[0] += 32;
        }
        return;
    case 2:
        if (v == 1)
            loop(i, len) {
            if (s[i] == '_') {
                cout << char(s[i + 1] - 32);
                ++i;
            }
            else cout << s[i];
        }
        if (v == 3) {
            s[0] -= 32;
            loop(i, len) {
                if (s[i] == '_') {
                    cout << char(s[i + 1] - 32);
                    ++i;
                }
                else cout << s[i];
            }
            s[0] += 32;
        }
        return;
    case 3:
        s[0] += 32;
        if (v == 1) cout << s;
        if (v == 2)
            loop(i, len) {
            if (s[i] < 'a')
                cout << '_' << char(s[i] + 32);
            else cout << s[i];
        }
        s[0] -= 32;
        return;
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n;
    string s;
    cin >> n >> s;
    for (int i = 1; i <= 3; ++i) {
        conv(s, n, i);
        cout << '\n';
    }
    return 0;
}