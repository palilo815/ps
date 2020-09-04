#include <bits/stdc++.h>
using namespace std;

const int mxS = 1e6;

int S, C, a[mxS];

bool make(int m) {
    int cnt = 0;
    for (int i = 0; i < S; ++i)
        if ((cnt += a[i] / m) >= C)
            return true;
    return false;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> S >> C;
    for (int i = 0; i < S; ++i)
        cin >> a[i];

    long long total = accumulate(a, a + S, 0ll);
    int l = 1, r = 1e9 + 1, ans;
    while (l ^ r) {
        int m = (l + r) >> 1;
        make(m) ? (l = m + 1, ans = m) : (r = m);
    }
    cout << total - 1ll * ans * C;
    return 0;
}