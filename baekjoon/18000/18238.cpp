#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s; cin >> s;
    int len = s.size(), curr = 0, ans = 0;
    loop(i, len) {
        int next_char = s[i] - 'A';
        ans += min((26 + curr - next_char) % 26, (26 + next_char - curr) % 26);
        curr = next_char;
    }
    cout << ans;
    return 0;
}