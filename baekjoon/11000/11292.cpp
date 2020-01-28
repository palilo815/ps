#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n;
    double h;
    string s;
    while (1) {
        cin >> n;
        if (n == 0) break;
        vector<string> ans;
        double M = 0;
        while (n--) {
            cin >> s >> h;
            if (h > M) { M = h; ans.clear(), ans.push_back(s); }
            else if (h == M) ans.push_back(s);
        }
        for (string& Nm : ans)
            cout << Nm << ' ';
        cout << '\n';
    }
    return 0;
}