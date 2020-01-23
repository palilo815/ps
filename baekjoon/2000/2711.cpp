#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int n;
        string s;
        cin >> n >> s;
        loop(i, s.size())
            if (i != n - 1) cout << s[i];
        cout << '\n';
    }
    return 0;
}