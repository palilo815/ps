#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t; cin >> t;
    string s;
    while (t--) {
        int n; cin >> n;
        int i = 0;
        vector<string> v1, v2;
        while (i++ < n) {
            cin >> s;
            v1.push_back(s);
            if (s[0] != '#') break;
        }
        while (i++ < n) {
            cin >> s;
            v2.push_back(s);
        }
        loop(j, v2.size())
            cout << v2[j] << ' ';
        if (v1[v1.size() - 1][0] != '#') {
            cout << v1[v1.size() - 1] << ' ';
            v1.pop_back();
        }
        loop(j, v1.size())
            cout << v1[j] << ' ';
        cout << '\n';
    }
    return 0;
}