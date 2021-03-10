#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5 + 1;

int ans, f[mxN], s[mxN], own[mxN];

void take(int cow, int cereal) {
    int prv = own[cereal];
    own[cereal] = cow;

    if (prv) {
        if (f[prv] == cereal && !own[s[prv]] || own[s[prv]] > prv)
            take(prv, s[prv]);
    } else
        ++ans;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;

    for (int i = 1; i <= N; ++i)
        cin >> f[i] >> s[i];

    vector<int> vt(N);
    for (int i = N; i; --i) {
        take(i, f[i]);
        vt[i - 1] = ans;
    }

    for (int& x : vt)
        cout << x << '\n';
}