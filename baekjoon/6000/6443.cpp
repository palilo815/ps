#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t; cin >> t;
    string s;
    while (t--) {
        cin >> s;
        sort(s.begin(), s.end());
        do {
            cout << s << '\n';
        } while (next_permutation(s.begin(), s.end()));
    }
    return 0;
}