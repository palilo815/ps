#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string a, b, c;
    while (cin >> a) {
        if (a == "#") break;
        vector<char> ans;
        cin >> b >> c;
        int len = a.size();
        loop(i, len) {
            int gap = b[i] - a[i];
            if (gap < 0) gap += 26;

            char n = c[i] - 26 + gap;
            if (n < 'a') n += 26;
            ans.push_back(n);
        }

        cout << a << ' ' << b << ' ' << c << ' ';
        loop(i, len) cout << ans[i];
        cout << '\n';
    }
    return 0;
}