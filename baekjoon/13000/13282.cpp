#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int MAX = 7368792;
    bitset<MAX> erased;
TOP:;
    int m, n;
    cin >> m >> n;
    if (!m && !n) {
        return 0;
    }
    erased.reset();
    int i = m;
    for (;; ++i) {
        if (!erased[i]) {
            if (!n--) {
                break;
            }
            for (int j = i; j < MAX; j += i) {
                erased.set(j);
            }
        }
    }
    cout << i << '\n';
    goto TOP;
}