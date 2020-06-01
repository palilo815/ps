#include <bits/stdc++.h>
#define all(v) v.begin(),v.end()
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, Q; cin >> N >> Q;
    vector<pair<string, int>> word(N);

    for (int i = 0; i < N; ++i)
        cin >> word[i].first,
        word[i].second = i + 1;
    sort(all(word));

    while (Q--) {
        int k; string s;
        cin >> k >> s;

        auto lo = lower_bound(all(word), make_pair(s, 0));
        s.back() += 1;
        auto hi = upper_bound(all(word), make_pair(s, 0));

        if (hi - lo < k) cout << -1;
        else cout << (lo + k - 1)->second;
        cout << '\n';
    }
    return 0;
}