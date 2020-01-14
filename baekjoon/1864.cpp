#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

char arr[8] = { '-', '\\', '(', '@', '?', '>', '&', '%' };
int Oword(char c)
{
    loop(i, 8)
        if (c == arr[i]) return i;
    return -1;
}
int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    while (1) {
        cin >> s;
        if (s == "#") break;
        reverse(s.begin(), s.end());
        int ans = 0;
        loop(i, s.size())
            ans += pow(8, i) * Oword(s[i]);
        cout << ans << '\n';
    }
    return 0;
}