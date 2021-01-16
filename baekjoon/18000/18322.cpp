#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;

    char s[81];
    for (int cur = 0, len; n--; cout << s) {
        cin >> s;
        len = strlen(s);
        if (cur + len > k) {
            cout << '\n';
            cur = 0;
        }
        if (cur) cout << ' ';
        cur += len;
    }
}