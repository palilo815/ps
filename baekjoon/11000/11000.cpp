#include <bits/stdc++.h>
using namespace std;

const int max_N = 200000;

int s[max_N], e[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> s[i] >> e[i];

    sort(s, s + N);
    sort(e, e + N);

    int i = 0, j = 0, ans = 1, cnt = 0;
    while (i < N) {
        if (s[i] < e[j]) {
            ++i;
            ans = max(ans, ++cnt);
        }
        else if (s[i] >= e[j])
            ++j, --cnt;
    }
    cout << ans;
    return 0;
}