#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t; cin >> t; cin.ignore();
    string s;
    while (t--) {
        getline(cin, s);
        int start = 0;
        while (s[start] != ' ') ++start;
        ++start;
        while (s[start] != ' ') ++start;

        for (int i = start + 1; i < s.size(); ++i)
            cout << s[i];
        cout << ' ';
        loop(i, start) cout << s[i];
        cout << '\n';
    }
    return 0;
}