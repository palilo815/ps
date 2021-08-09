#include <bits/stdc++.h>
using namespace std;

struct elem {
    int val, x, y;
};

constexpr int MX_N = 1e3;

int a[MX_N];
elem ab[MX_N * (MX_N - 1) / 2];
elem dc[MX_N * (MX_N - 1) / 2];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
TOP:;
    cin >> n;
    if (!n) return 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int m = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ab[m] = {a[i] + a[j], a[i], a[j]};
            dc[m] = {a[j] - a[i], a[i], a[j]};
            ++m;
        }
    }
    sort(ab, ab + m, [&](const auto& lhs, const auto& rhs) {
        return lhs.val < rhs.val;
    });
    sort(dc, dc + m, [&](const auto& lhs, const auto& rhs) {
        return lhs.val < rhs.val;
    });
    int best = INT_MIN;
    for (int i = 0, j = 0, k = m - 1; i < m; ++i) {
        while (j != m && dc[j].val < ab[i].val) ++j;
        while (k != -1 && -dc[k].val < ab[i].val) --k;
        for (int it = j; it != m && ab[i].val == dc[it].val; ++it) {
            if (dc[it].y > best && ab[i].x != dc[it].x && ab[i].x != dc[it].y && ab[i].y != dc[it].x && ab[i].y != dc[it].y) {
                best = dc[it].y;
            }
        }
        for (int it = k; it != -1 && ab[i].val == -dc[it].val; --it) {
            if (dc[it].x > best && ab[i].x != dc[it].x && ab[i].x != dc[it].y && ab[i].y != dc[it].x && ab[i].y != dc[it].y) {
                best = dc[it].x;
            }
        }
    }
    if (best == INT_MIN) {
        cout << "no solution\n";
    } else {
        cout << best << '\n';
    }
    goto TOP;
}