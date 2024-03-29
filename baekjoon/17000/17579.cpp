#include <bits/stdc++.h>
using namespace std;

constexpr int MX_N = 100;
constexpr int MX_M = 10;
constexpr int MX_K = 59049; // 3^10

int a[MX_N], w[MX_M], sum[MX_K], not_found[MX_N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

TOP:;
    int n, m;
    cin >> n >> m;
    if (n == 0 && m == 0) return 0;

    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < m; ++i)
        cin >> w[i];

    int k = pow(3, m);

    for (int mask = 0; mask < k; ++mask) {
        int lsum = 0, rsum = 0;
        for (int i = 0, m = mask; m; m /= 3, ++i) {
            if (m % 3 == 1)
                lsum += w[i];
            else if (m % 3 == 2)
                rsum += w[i];
        }
        sum[mask] = abs(lsum - rsum);
    }

    sort(sum, sum + k);
    k = unique(sum, sum + k) - sum;

    int missing_count = 0;
    for (int i = 0; i < n; ++i)
        if (!binary_search(sum, sum + k, a[i]))
            not_found[missing_count++] = a[i];

    if (missing_count) {
        vector<int> candidate;
        candidate.reserve(k << 1);
        for (int i = 0; i < k; ++i) {
            candidate.emplace_back(abs(not_found[0] - sum[i]));
            candidate.emplace_back(not_found[0] + sum[i]);
        }
        for (int i = 1; i < missing_count; ++i)
            candidate.erase(remove_if(candidate.begin(), candidate.end(), [&](const auto& x) {
                return !binary_search(sum, sum + k, abs(x - not_found[i])) && !binary_search(sum, sum + k, x + not_found[i]);
            }),
                candidate.end());
        cout << (candidate.empty() ? -1 : *min_element(candidate.begin(), candidate.end()));
    } else {
        cout << 0;
    }
    cout << '\n';
    goto TOP;
}