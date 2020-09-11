#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e4;

int a[mxN], ord[mxN + 1], p[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i];
    for (int i = 0, x; i < N; ++i) {
        cin >> x;
        ord[x] = i;
    }

    vector<int> T = {ord[a[0]]};

    for (int i = 1; i < N; ++i) {
        if (ord[a[i]] > T.back()) {
            p[i] = T.size();
            T.emplace_back(ord[a[i]]);
        }
        else {
            auto it = lower_bound(T.begin(), T.end(), ord[a[i]]);
            *it = ord[a[i]];
            p[i] = it - T.begin();
        }
    }

    vector<int> ans;
    for (int i = N - 1, pos = T.size() - 1; ~i; --i)
        if (p[i] == pos) {
            --pos;
            ans.emplace_back(a[i]);
        }

    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (int& x : ans) cout << x << ' ';
    return 0;
}