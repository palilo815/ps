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
    char prv = '#';
    for (string s; n--;) {
        cin >> s;
        if (prv == '#') prv = *s.begin();
        else if (prv != *s.begin())
            return cout << 0, 0;
    }
    cout << 1;
}