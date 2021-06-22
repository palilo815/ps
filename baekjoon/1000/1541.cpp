#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    string s;
    cin >> s;
    s += '!';

    int ans = 0, sum = 0;
    bool minus = false;

    for (const auto& c : s) {
        if (isdigit(c)) sum = (sum * 10) + c - '0';
        else {
            ans += minus ? -sum : sum;
            if (c == '-') minus = true;
            sum = 0;
        }
    }
    cout << ans;
}