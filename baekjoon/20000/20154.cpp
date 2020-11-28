#include <bits/stdc++.h>
using namespace std;

const int cnt[26] = {3, 2, 1, 2, 3, 3, 3, 3, 1, 1, 3, 1, 3, 3, 1, 2, 2, 2, 1, 2, 1, 1, 2, 2, 2, 1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    string s;
    cin >> s;

    vector<int> a((s.size() + 1) >> 1);
    for (int i = 0, j = 0; i < s.size(); i += 2, ++j)
        a[j] = i + 1 == s.size() ? cnt[s[i] - 'A'] : cnt[s[i] - 'A'] + cnt[s[i + 1] - 'A'];

    while (a.size() != 1) {
        int sz = (a.size() + 1) >> 1;
        for (int i = 0, j = 0; i < a.size(); i += 2, ++j)
            a[j] = i + 1 == a.size() ? a[i] : a[i] + a[i + 1];
        a.resize(sz);
    }
    cout << (a[0] & 1 ? "I'm a winner!" : "You're the winner?");
}