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
    if (!(n & 1)) return cout << "NOT POSSIBLE", 0;

    string s;
    cin >> s;

    auto ok = [&](int i, int ed, int j) -> bool {
        for (bool inserted = false; i != ed; ++i, ++j)
            if (s[i] != s[j]) {
                if (inserted) return false;
                inserted = true;
                --i;
            }
        return true;
    };

    bool front = ok(0, n >> 1, n >> 1), back = ok((n >> 1) + 1, n, 0);
    if (front && back)
        cout << (equal(s.begin(), s.begin() + (n >> 1), s.begin() + (n >> 1) + 1) ? s.substr(0, n >> 1) : "NOT UNIQUE");
    else if (front)
        cout << s.substr(0, n >> 1);
    else if (back)
        cout << s.substr((n >> 1) + 1);
    else
        cout << "NOT POSSIBLE";
}