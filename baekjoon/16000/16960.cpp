#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, m;
    cin >> n >> m;

    vector<vector<int>> links(n);
    for (auto& link : links) {
        int cnt;
        cin >> cnt;

        link.resize(cnt);
        for (auto& x : link) cin >> x, --x;
    }

    vector<int> cnt(m);
    for (const auto& link : links)
        for (const auto& x : link)
            ++cnt[x];

    cout << any_of(links.begin(), links.end(), [&](auto& link) {
        return all_of(link.begin(), link.end(), [&](auto& x) {
            return cnt[x] > 1;
        });
    });
}