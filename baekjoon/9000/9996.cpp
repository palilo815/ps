#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    const auto [pref, suff] = [&]() {
        string s;
        cin >> s;
        const auto star = s.find('*');
        return make_pair(s.substr(0, star), s.substr(star + 1));
    }();
    for (string s; n--;) {
        cin >> s;
        if (s.size() >= pref.size() + suff.size() &&
            equal(pref.begin(), pref.end(), s.begin()) &&
            equal(suff.begin(), suff.end(), s.end() - suff.size())) {
            cout << "DA\n";
        } else {
            cout << "NE\n";
        }
    }
}