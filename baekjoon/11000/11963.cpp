#include <bits/stdc++.h>
using namespace std;

const int mxN = 5e4;

bool used[(mxN + 1) << 1];
int a[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
        used[a[i]] = true;
    }

    sort(a, a + (N >> 1));
    sort(a + (N >> 1), a + N, greater<int>());

    int piv = 1;
    for (int half = N >> 1, cnt = 0; cnt ^ half; ++piv)
        if (!used[piv])
            ++cnt;

    int ans = 0;
    for (int i = 0, j = piv;; ++j) {
        while (used[j]) ++j;
        if (j == (N << 1 | 1)) break;
        if (j > a[i]) ++i, ++ans;
    }
    for (int i = N >> 1, j = piv - 1;; --j) {
        while (used[j]) --j;
        if (!j) break;
        if (j < a[i]) ++i, ++ans;
    }
    cout << ans;
    return 0;
}