#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    string a, b, c;
    long long r;
    cin >> a >> b >> r;
    c = to_string(r);

    if (a == "0" || b == "0") {
        cout << 0;
        return 0;
    }

    auto overflow = [&](const string& s) {
        return s.size() == c.size() ? s > c : s.size() > c.size();
    };
    if (overflow(a) || overflow(b) || stoll(a) > r / stoll(b))
        cout << "overflow";
    else
        cout << stoll(a) * stoll(b);
    cout << '\n';
    return 0;
}