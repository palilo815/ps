#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;

    vector<int> num(M);
    for (int& x : num)
        cin >> x;

    set<int> st[2];
    st[0].insert(num.begin(), num.end());

    for (int i = 0; i < N; ++i) {
        st[1 - (i & 1)].clear();
        for (int x : st[i & 1])
            for (int& y : num)
                st[1 - (i & 1)].emplace(x + y), st[1 - (i & 1)].emplace(x * y);
    }

    cin >> M;
    while (M--) {
        int x; cin >> x;
        cout << (st[N & 1].count(x) ? "Y\n" : "N\n");
    }
    return 0;
}