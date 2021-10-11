#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int k;
    string s;
    cin >> k >> s;
    for (int i = 0; i < int(s.size()); i += k) {
        cout << s[i];
    }
}