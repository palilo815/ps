#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s; cin >> s;
    if (next_permutation(s.begin(), s.end()))
        cout << s;
    else cout << 0;
    return 0;
}