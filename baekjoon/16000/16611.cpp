#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    vector<char> en(m), de(m);
    for (int i = m - n; i < m; ++i)
        cin >> de[i];
    for (int i = 0; i < m; ++i)
        cin >> en[i];

    for (int i = m - n - 1; ~i; --i)
        de[i] = (26 - de[i + n] + en[i + n]) % 26 + 'a';

    for (auto& x : de) cout << x;
}