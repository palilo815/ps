#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

int s[mxN], e[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0, x; i < N; ++i)
        cin >> s[i] >> e[i];

    sort(s, s + N);
    sort(e, e + N);

    int ans = 0;
    for (int i = 0, j = 0, cnt = 0; i < N;) {
        if (s[i] < e[j])
            ++i, ans = max(ans, ++cnt);
        else
            ++j, --cnt;
    }
    cout << ans;
    return 0;
}