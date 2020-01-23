#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

bool used[26];
int main()
{
    string s;
    int T; cin >> T; cin.ignore();
    while (T--) {
        memset(used, 0, sizeof(used));
        getline(cin, s);

        for (char c : s) {
            if (c >= 'a' && c <= 'z') used[c - 'a'] = true;
            else if (c >= 'A' && c <= 'Z') used[c - 'A'] = true;
        }

        vector<char> missed;
        loop(i, 26)
            if (!used[i]) missed.push_back('a' + i);

        if (!missed.empty()) {
            cout << "missing ";
            for (char c : missed) cout << c;
            cout << '\n';
        }
        else cout << "pangram\n";
    }
    return 0;
}