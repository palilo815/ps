#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;

    bitset<1000001> ck;
    int ans = 0;
    for (int a, b, c; N--;) {
        cin >> a >> b >> c;
        if (!ck[a] && !ck[b] && !ck[c]) ++ans;
        ck[a] = ck[b] = ck[c] = 1;
    }
    cout << ans;
    return 0;
}