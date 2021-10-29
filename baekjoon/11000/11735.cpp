#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    int64_t rsum = int64_t(n + 1) * n / 2, csum = rsum;
    int64_t rcnt = n, ccnt = n;
    vector<bool> row(n + 1), col(n + 1);
    char op;
    for (int64_t x; m--;) {
        cin >> op >> x;
        if (op == 'R') {
            if (!row[x]) {
                row[x] = true;
                rsum -= x, --rcnt;
                cout << csum + ccnt * x << '\n';
            } else {
                cout << "0\n";
            }
        } else {
            if (!col[x]) {
                col[x] = true;
                csum -= x, --ccnt;
                cout << rsum + rcnt * x << '\n';
            } else {
                cout << "0\n";
            }
        }
    }
}