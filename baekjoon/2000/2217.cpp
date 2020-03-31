#include <bits/stdc++.h>
using namespace std;

const int max_N = 100000;

int w[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 0; i < N; ++i) cin >> w[i];
    sort(w, w + N);

    int cnt = 1, ans = 0;
    for (int i = N - 1; i >= 0; --i) {
        int tmp = w[i] * cnt;
        if (tmp > ans)
            ans = tmp;
        ++cnt;
    }
    cout << ans;
    return 0;
}