#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    char s[7];
    auto ask = [&](int x) {
        cout << x << endl;
        cin >> s;
        if (s[0] == 'V') exit(0);
    };

    ask(0);

    char key = s[0];
    int lo = 0, hi = n;
    while (lo != hi) {
        int m = (lo + hi) >> 1;
        ask(m);
        (key == s[0]) == (m & 1) ? hi = m : lo = m + 1;
    }
    ask(lo);
}