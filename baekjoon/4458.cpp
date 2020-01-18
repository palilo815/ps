#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    string s;
    int t; cin >> t;
    cin.ignore();
    while (t--) {
        getline(cin, s);
        if (s[0] > 'Z') s[0] -= 32;
        cout << s << '\n';
    }
    return 0;
}