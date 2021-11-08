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
    cout << accumulate(s.begin(), s.end(), 0, [&](const auto& sum, const auto& x) {
        const auto y = x - '0';
        return sum + y * y * y * y * y;
    });
}