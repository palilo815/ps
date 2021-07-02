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

    auto it = s.find('.');
    int64_t num = stoi(s.substr(0, it)) * 100 + (s[it + 1] - '0') * 10 + (s[it + 2] - '0');

    cout << lcm(num, int64_t(36000)) / num;
}