#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s, t; cin >> s >> t;
    int gap = t.size() - s.size();
    int L = 0, R = t.size() - 1, d = 1;
    while (gap--) {
        if (t[R] == 'A') R -= d;
        else {
            R -= d;
            swap(L, R);
            d = -d;
        }
    }
    for (int i = 0; i < s.size(); ++i)
        if (s[i] != t[L + d * i]) {
            cout << 0;
            return 0;
        }
    cout << 1;
    return 0;
}