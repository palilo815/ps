#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int64_t k;
    string s;
    cin >> k >> s;

    int ans = 0;
    for (; stoll(s, nullptr, 2) > k; ++ans)
        if (auto it = find(s.begin() + 1, s.end(), '1'); it == s.end())
            s.pop_back();
        else
            s.erase(it);
    cout << ans;
}