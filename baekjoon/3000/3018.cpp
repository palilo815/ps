#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, e;
    cin >> n >> e;

    vector<bitset<50>> know(n);
    int song = 0;

    vector<int> member;
    for (int k; e--;) {
        cin >> k;
        member.resize(k);
        for (auto& x : member) cin >> x, --x;

        if (bool bard = find(member.begin(), member.end(), 0) != member.end(); bard) {
            for (const auto& x : member)
                know[x][song] = true;
            ++song;
        } else {
            bitset<50> orsum;
            for (const auto& x : member)
                orsum |= know[x];
            for (const auto& x : member)
                know[x] = orsum;
        }
    }

    for (int i = 0; i < n; ++i)
        if (know[i].count() == song)
            cout << i + 1 << '\n';
}