#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n;
    cin >> n;

    vector<string> grid(n);
    for (auto& x : grid) cin >> x;

    vector<int> row_sum(n), col_sum(n);
    vector<int> row_con(n), col_con(n);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 'B') {
                ++row_sum[i], ++col_sum[j];
                if (row_con[i] < 0) row_con[i] = 0;
                if (col_con[j] < 0) col_con[j] = 0;
                if (++row_con[i] == 3 || ++col_con[j] == 3)
                    return cout << 0, 0;
            } else {
                if (row_con[i] > 0) row_con[i] = 0;
                if (col_con[j] > 0) col_con[j] = 0;
                if (--row_con[i] == -3 || --col_con[j] == -3)
                    return cout << 0, 0;
            }
        }

    cout << (all_of(row_sum.begin(), row_sum.end(), [&](const auto& x) { return x == n / 2; }) &&
             all_of(col_sum.begin(), col_sum.end(), [&](const auto& x) { return x == n / 2; }));
}