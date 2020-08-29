#include <bits/stdc++.h>
using namespace std;

const int mxM = 1e3;

int m, ans[mxM];
char num[9];

int solve() {
    int x = 0;
    for (int i = 2; i < 8; ++i) {
        x *= 10;
        if (num[i]) x += num[i] - '0';
    }
    return x * m / 1000000;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> m;
    while (cin >> num)
        ++ans[solve()];
    for (int i = 0; i < m; ++i)
        cout << ans[i] << ' ';
    return 0;
}