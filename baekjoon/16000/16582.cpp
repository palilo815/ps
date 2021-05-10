#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int MX_S = 15;

    struct c_string {
        char s[MX_S + 1];
    };

    int n;
    cin >> n;

    // dp[i] = 이름 길이 총합이 i가 되는 마지막 아이의 이름 중 가장 사건순으로 앞서는 것
    vector<c_string> dp(n * MX_S + 1), prv(n * MX_S + 1);

    vector<c_string> names;
    names.reserve((1 << MX_S) - 1);

    c_string candidate;
    char buf[MX_S + 1];

    for (int i = 0; i < n; ++i) {
        dp.swap(prv);
        memset(dp.data(), 0, dp.size() * sizeof(c_string));

        cin >> buf;
        int len = strlen(buf);

        names.clear();
        for (int mask = 1; mask < 1 << len; ++mask) {
            int pos = 0;
            for (int j = 0; j < len; ++j)
                if (mask >> j & 1)
                    candidate.s[pos++] = buf[j];
            candidate.s[pos] = '\0';
            names.push_back(candidate);
        }

        sort(names.begin(), names.end(), [&](auto& a, auto& b) {
            return strcmp(a.s, b.s) < 0;
        });

        for (int sz = MX_S * (i + 1); sz; --sz) {
            int it = 0;
            for (; it < int(names.size()); ++it) {
                int len = strlen(names[it].s);
                if ((i == 0 && len == sz) ||
                    (len < sz && prv[sz - len].s[0] && strcmp(names[it].s, prv[sz - len].s) > 0))
                    break;
            }
            if (it != int(names.size()))
                strcpy(dp[sz].s, names[it].s);
        }
    }

    cout << dp.rend() - find_if(dp.rbegin(), dp.rend(), [&](auto& x) { return x.s[0]; }) - 1;
}