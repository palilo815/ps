#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    constexpr array ans = {
        "Not a pangram\n",
        "Pangram!\n",
        "Double pangram!!\n",
        "Triple pangram!!!\n"};

    int T;
    cin >> T;
    cin.ignore();

    string s;
    array<int, 26> cnt;

    for (int t = 1; t <= T; ++t) {
        getline(cin, s);
        fill(cnt.begin(), cnt.end(), 0);

        for (const auto& c : s)
            if (isalpha(c))
                ++cnt[c - (islower(c) ? 'a' : 'A')];

        cout << "Case " << t << ": "
             << ans[*min_element(cnt.begin(), cnt.end())];
    }
}