#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool check[26];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    while (getline(cin, s)) {
        if (s == "END") break;
        memset(check, 0, sizeof(check));
        loop(i, s.size()) {
            if (s[i] == ' ') continue;
            int ind = s[i] - 'A';
            if (check[ind]) break;
            check[ind] = true;
            if (i == s.size() - 1) cout << s << '\n';
        }
    }
    return 0;
}