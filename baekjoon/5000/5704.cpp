#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    bool used[26];
    while (1) {
        getline(cin, s);
        if (s == "*") break;
        memset(used, 0, sizeof(used));
        loop(i, s.size())
            if (s[i] != ' ') used[s[i] - 'a'] = true;

        bool pangram = true;
        loop(i, 26)
            if (!used[i]) pangram = false;
        if (pangram) cout << "Y\n";
        else cout << "N\n";
    }
    return 0;
}