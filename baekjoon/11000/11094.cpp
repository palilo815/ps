#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s, key = "Simon says";
    int T; cin >> T; cin.ignore();
    while (T--) {
        getline(cin, s);
        if (s.substr(0, 10) == key) {
            for (int i = 10; i < s.size(); ++i) cout << s[i];
            cout << '\n';
        }
    }
    return 0;
}