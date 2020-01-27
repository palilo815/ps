#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    int T; cin >> T;
    while (T--) {
        cin >> s;
        string tmp = s;
        if (next_permutation(s.begin(), s.end()))
            cout << s;
        else cout << tmp;
        cout << '\n';
    }
    return 0;
}