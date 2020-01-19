#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    bool check[26];
    int T;
    cin >> T;
    string s;
    while (T--) {
        memset(check, 0, sizeof(check));
        cin >> s;
        loop(i, s.size()) {
            char c = s[i];
            if (c >= 'a' && c <= 'z') check[c - 'a'] = true;
            else if (c >= 'A' && c <= 'Z') check[c - 'A'] = true;
        }
        bool Opp = true;
        loop(i, 26)
            if (check[i] && !check[25 - i]) Opp = false;
        if (Opp) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}