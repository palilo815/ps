#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int find_joke(string& s)
{
    int ret = 0, len = s.size();
    loop(i, len - 3) {
        if (s[i] == 'j') {
            if (s[i + 1] == 'o') {
                if (s[i + 2] == 'k') {
                    if (s[i + 3] == 'e') {
                        ++ret;
                        i += 3;
                    }
                    else i += 2;
                }
                else ++i;
            }
        }
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    int ans = 0;
    while (cin >> s)
        ans += find_joke(s);
    cout << ans;
    return 0;
}