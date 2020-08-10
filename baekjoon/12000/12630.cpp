#include <bits/stdc++.h>
using namespace std;

const int mxN = 40;

char s[mxN + 1];

int solve() {
    int N; cin >> N;
    vector<int> vt(N);

    for (auto& x : vt) {
        cin >> s;
        int i = N - 1;
        while (~i && s[i] == '0') --i;
        x = i;
    }

    int ans = 0;
    for (int i = 0; i < N; ++i) {
        auto it = find_if(vt.begin(), vt.end(), [&](auto & x) {
            return x <= i;
        });
        ans += it - vt.begin();
        vt.erase(it);
    }
    return ans;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        cout << "Case #" << t << ": " << solve() << '\n';
    return 0;
}