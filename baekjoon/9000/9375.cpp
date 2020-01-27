#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    string name, kind;
    int T, n; cin >> T;
    while (T--) {
        cin >> n;
        map<string, int> mp;
        int ans = 1;
        while (n--) {
            cin >> name >> kind;
            if (mp.find(kind) == mp.end())
                mp[kind] = 1;
            else
                ++mp[kind];
        }
        for (auto it = mp.begin(); it != mp.end();++it)
            ans *= it->second + 1;
        cout << ans - 1 << '\n';
    }
    return 0;
}