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
    const auto f1 = s.find('/'), f2 = s.find('/', f1 + 1);
    const auto k = stoi(s.substr(0, f1)), d = stoi(s.substr(f1 + 1, f2 - f1)), a = stoi(s.substr(f2 + 1));
    cout << ((k + a < d || !d) ? "hasu" : "gosu");
}