#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    vector<string> vt;
    vector<string> ans;
    
    string s;
    int N, M; cin >> N >> M;
    while (N--) {
        cin >> s;
        vt.emplace_back(s);
    }
    sort(vt.begin(), vt.end());

    while (M--) {
        cin >> s;
        if (binary_search(vt.begin(), vt.end(), s))
            ans.emplace_back(s);
    }
    sort(ans.begin(), ans.end());

    cout << ans.size() << '\n';
    for (string x : ans) cout << x << '\n';
    return 0;
}