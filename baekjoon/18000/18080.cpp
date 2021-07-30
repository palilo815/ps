#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, w;
    cin >> n >> w;
    vector<int64_t> rank(n);
    vector<int64_t> sum(w + 1);
    vector<int> score(n), leave(w + 1);
    for (int i = 0, k, x; i < w; ++i) {
        for (cin >> k; k--;) {
            cin >> x, --x;
            const int64_t t = w - i;
            rank[x] += (sum[score[x]] - t * leave[score[x]]) -
                       (sum[score[x] + 1] - t * leave[score[x] + 1]);
            sum[score[x]] += t;
            ++leave[score[x]++];
        }
    }
    for (int i = 0; i < n; ++i) {
        rank[i] += w + sum[score[i]];
    }
    cout << fixed << setprecision(7);
    for (const auto& x : rank) {
        cout << double(x) / w << '\n';
    }
}