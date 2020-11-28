#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;

    vector<int> cnt(M + 1);
    for (int i = 0, x; i < N; ++i) {
        cin >> x;
        ++cnt[x];
    }

    cout << *max_element(cnt.begin(), cnt.end());
}