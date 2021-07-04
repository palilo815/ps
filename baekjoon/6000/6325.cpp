#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    array<bool, 26> assigned;
    int TC = 0;
TOP:;
    assigned.fill(false);
    assigned[0] = true;
    int n;
    cin >> n;
    if (!n) {
        return 0;
    }
    for (char a, op, b; n--;) {
        cin >> a >> op >> b;
        assigned[a - 'a'] = assigned[b - 'a'];
    }
    cout << "Program #" << ++TC << '\n';
    bool flag = false;
    for (int i = 0; i < 26; ++i) {
        if (assigned[i]) {
            flag = true;
            cout << char(i + 'a') << ' ';
        }
    }
    if (!flag) {
        cout << "none";
    }
    cout << '\n'
         << '\n';
    goto TOP;
}