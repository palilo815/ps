#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    string s;
    cin >> s;

    const int n = s.size();

    vector<int> psum(n + 1);
    for (int i = 0; i < n; ++i)
        psum[i + 1] = s[i] == 'R';
    for (int i = 0; i < n; ++i)
        psum[i + 1] += psum[i];

    auto ans = psum.back();
    for (int i = 0, j = n - 1, cntK = 2;; ++i, --j, cntK += 2) {
        while (i < n && s[i] == 'R') ++i;
        while (~j && s[j] == 'R') --j;
        if (int cntR = psum[j] - psum[i]; cntR > 0)
            ans = max(ans, cntK + cntR);
        else
            break;
    }
    cout << ans;
}