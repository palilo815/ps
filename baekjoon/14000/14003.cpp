#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e6;

int a[mxN], p[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i];

    vector<int> T = {a[0]};

    for (int i = 1; i < N; ++i) {
        if (a[i] > T.back()) {
            p[i] = T.size();
            T.emplace_back(a[i]);
        }
        else {
            auto it = lower_bound(T.begin(), T.end(), a[i]);
            *it = a[i];
            p[i] = it - T.begin();
        }
    }

    vector<int> ans;
    for (int i = N - 1, pos = T.size() - 1; ~pos; --i)
        if (p[i] == pos) {
            ans.emplace_back(a[i]);
            --pos;
        }

    cout << ans.size() << '\n';
    for (auto it = ans.rbegin(); it != ans.rend(); ++it)
        cout << *it << ' ';
    return 0;
}