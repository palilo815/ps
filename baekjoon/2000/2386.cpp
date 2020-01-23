#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    std::ios::sync_with_stdio(false);

    string s;
    while (1) {
        getline(cin, s);
        if (s == "#") break;
        int ans = 0;
        char key = s[0];
        char KEY = key - 'a' + 'A';
        for (int i = 2; i < s.size(); ++i)
            if (s[i] == key || s[i] == KEY) ++ans;
        cout << key << ' ' << ans << '\n';
    }
    return 0;
}