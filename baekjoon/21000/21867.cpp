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
    s.erase(remove_if(s.begin(), s.end(), [&](const auto& x) { return x == 'J' || x == 'A' || x == 'V'; }), s.end());
    cout << (s.empty() ? "nojava" : s);
}