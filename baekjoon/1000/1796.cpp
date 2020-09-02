#include <bits/stdc++.h>
using namespace std;

char s[1001];
int l[26], r[26];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> s;
    int ans = 0;
    for (int i = 0; s[i]; ++i, ++ans) {
        int k = s[i] - 'a';
        if (!l[k]) l[k] = i + 1;
        r[k] = i + 1;
    }

    int l_pos = 1, r_pos = 1, l_dp = 0, r_dp = 0;
    for (int i = 0; i < 26; ++i) {
        if (!l[i]) continue;
        int nxt_l  = abs(l[i] - r[i]) + min(abs(r[i] - l_pos) + l_dp, abs(r[i] - r_pos) + r_dp);
        int nxt_r  = abs(l[i] - r[i]) + min(abs(l[i] - l_pos) + l_dp, abs(l[i] - r_pos) + r_dp);
        l_dp = nxt_l, r_dp = nxt_r;
        l_pos = l[i], r_pos = r[i];
    }

    cout << ans + min(l_dp, r_dp);
    return 0;
}