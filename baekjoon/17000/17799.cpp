#include <bits/stdc++.h>
using namespace std;

int w[100000];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, C; cin >> N >> C;
    for (int i = 0; i < N; ++i) cin >> w[i];
    sort(w, w + N);

    int i = 0, j = N - 1, ans = 0;
    while (i <= j) {
        if (w[i] + w[j] <= C) ++i;
        --j, ++ans;
    }
    cout << ans;
    return 0;
}