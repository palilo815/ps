#include <iostream>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    string s; cin >> s;
    int l = 0, r = s.size() - 1;

    char c = s[l];
    int pallin = 1, impossible = 1;
    while (l <= r) {
        if (s[l] != c || s[r] != c)
            impossible = 0;
        if (s[l] != s[r])
            pallin = 0;
        ++l, --r;
    }

    if (impossible) cout << -1;
    else if (pallin) cout << s.size() - 1;
    else cout << s.size();
    return 0;
}