#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

string s[100];
bool palin(string& s1, string& s2)
{
    string s = s1 + s2;
    int L = 0, R = s.size() - 1;
    while (L < R)
        if (s[L++] != s[R--]) return false;
    return true;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T, k;
    cin >> T;
    while (T--) {
        cin >> k;
        loop(i, k) cin >> s[i];
        string ans = "";
        loop(i, k) loop(j, k) {
            if (i == j || s[i][0] != s[j].back()) continue;
            if (palin(s[i], s[j])) {
                ans = s[i] + s[j];
                goto OUT;
            }
        }
    OUT:;
        if (ans == "") cout << "0\n";
        else cout << ans << '\n';
    }
    return 0;
}