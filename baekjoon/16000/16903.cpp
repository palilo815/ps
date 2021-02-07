#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int m;
    cin >> m;

    multiset<int> st = {0};
    char op;
    for (int x; m--;) {
        cin >> op >> x;
        if (op == '1')
            st.emplace(x);
        else if (op == '2')
            st.erase(st.find(x));
        else {
            int key = 0;
            for (int mask = 1 << 29; mask; mask >>= 1) {
                if (!(x & mask)) key |= mask;

                auto it = st.lower_bound(key);
                if (it == st.end() || *it >= key + mask)
                    key ^= mask;
            }
            cout << (x ^ key) << '\n';
        }
    }
}