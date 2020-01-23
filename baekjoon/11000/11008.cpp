#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s, key;
    int t; cin >> t;
    while (t--) {
        cin >> s >> key;
        int ans = 0, key_len = key.size();
        while (1) {
            auto F = s.find(key);
            if (F == string::npos) break;
            ++ans;
            s.erase(F, key_len);
        }
        cout << ans + s.size() << '\n';
    }
    return 0;
}