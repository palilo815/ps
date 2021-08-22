#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    string s;
    cin >> n >> s >> k;
    cout << (all_of(max(s.begin(), s.end() - k), s.end(), [&](const auto& x) { return x == '0'; })
                 ? "YES"
                 : "NO");
}