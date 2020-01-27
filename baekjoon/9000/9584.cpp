#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string key;
    vector<string> ans;
    int T;
    cin >> key >> T;
    while (T--) {
        string s; cin >> s;
        bool f = true;
        loop(i, s.size())
            if (key[i] != '*' && key[i] != s[i]) {
                f = false;
                break;
            }
        if (f) ans.push_back(s);
    }
    cout << ans.size() << '\n';
    for (string x : ans)
        cout << x << '\n';
    return 0;
}