#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    constexpr array leetspeak = {'O', 'L', 'Z', 'E', '#', 'S', 'B', 'T', 'B'};

    int n, m;
    cin >> n >> m;

    vector<string> bad(n);
    for (auto& x : bad) cin >> x;

    for (string s; m--;) {
        cin >> s;
        for (int i = 0; i < int(leetspeak.size()); ++i)
            replace(s.begin(), s.end(), char('0' + i), leetspeak[i]);
        if (any_of(bad.begin(), bad.end(), [&](const auto& x) { return s.find(x) != string::npos; }))
            cout << "IN";
        cout << "VALID\n";
    }
}