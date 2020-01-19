#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int ans[8];
vector<char> Key[8];
void Typing(char c)
{
    loop(i, 8) loop(j, Key[i].size())
        if (c == Key[i][j]) {
            ++ans[i];
            return;
        }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s; cin >> s;
    Key[0] = { '1','Q','A','Z' };
    Key[1] = { '2','W','S','X' };
    Key[2] = { '3','E','D','C' };
    Key[3] = { '4','5','R','T','F','G','V','B' };
    Key[4] = { '6','7','Y','U','H','J','N','M' };
    Key[5] = { '8','I','K',',' };
    Key[6] = { '9','O','L','.' };
    Key[7] = { '0','-','=','P','[',']',';','\'','/' };
    loop(i, s.size())
        Typing(s[i]);
    loop(i, 8)
        cout << ans[i] << '\n';
    return 0;
}