#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s; cin >> s;
    if (s[0] == '0') {
        if (s[1] == 'x') {
            reverse(s.begin(), s.end());
            int Ans = 0;
            loop(i, s.size() - 2) {
                int n = s[i] - '0';
                if (n > 9) n -= 39;
                Ans += n * pow(16, i);
            }
            cout << Ans;
        }
        else {
            reverse(s.begin(), s.end());
            int Ans = 0;
            loop(i, s.size() - 1)
                Ans += (s[i] - '0') * pow(8, i);
            cout << Ans;
        }
    }
    else cout << s;
    return 0;
}