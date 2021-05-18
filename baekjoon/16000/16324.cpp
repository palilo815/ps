#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    // 00 01 10 11

    int z = a ? sqrt(a << 1) + 1 : 0;
    int o = d ? sqrt(d << 1) + 1 : 0;
    if (!z && (b || c)) z = 1;
    if (!o && (b || c)) o = 1;
    if (z * (z - 1) != (a << 1) || o * (o - 1) != (d << 1) || b + c != z * o)
        return cout << "impossible", 0;

    string ans = string(z, '0') + string(o, '1');
    int cnt_01 = z * o;

    for (int i = z; i < z + o; ++i) {
        int mov = min(z, cnt_01 - b);
        swap(ans[i], ans[i - mov]);
        if (mov != z) break;
        cnt_01 -= z;
    }

    if (ans.empty()) ans = "0";
    cout << ans;
}