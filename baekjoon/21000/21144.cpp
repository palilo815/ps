#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n;
    string s;
    cin >> n >> s;

    for (int num = 1, i = 0; num < n; ++num, ++i) {
        if (num < 10) {
            if (s[i] - '0' != num)
                return cout << num, 0;
        } else {
            if ((s[i] - '0') * 10 + s[i + 1] - '0' != num)
                return cout << num, 0;
            ++i;
        }
    }
    cout << n;
}