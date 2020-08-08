#include <bits/stdc++.h>
using namespace std;

int solve() {
    string s;
    int k;
    cin >> s >> k;

    int ans = 0, N = s.size() - k;
    for (int i = 0; i <= N; ++i)
        if (s[i] == '-') {
            ++ans;
            for (int j = i + 1; j < i + k; ++j)
                s[j] = (s[j] == '+' ? '-' : '+');
        }
    for (int i = N + 1; i < s.size(); ++i)
        if (s[i] == '-')
            return -1;
    return ans;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    for (int i = 1; i <= T; ++i) {
        cout << "Case #" << i << ": ";
        int ans = solve();
        if (~ans) cout << ans;
        else cout << "IMPOSSIBLE";
        cout << '\n';
    }
    return 0;
}