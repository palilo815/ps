#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int MX_N = 32;
    constexpr double LIM = 5e-5, DELTA = 0.9999, k = 10;
    mt19937 rng(409);
    uniform_real_distribution<double> random_double(0, 1);
    int n;
    cin >> n;
    uniform_int_distribution<int> random_int(0, n - 1);
    vector<unsigned> best(n);
    {
        char buf[MX_N + 1];
        for (auto& x : best) {
            cin >> buf;
            for (int j = 0; j < n; ++j) {
                x <<= 1;
                if (buf[j] == 'T') x |= 1u;
            }
        }
    }
    const auto minimize = [&]() {
        return accumulate(best.begin(), best.end(), 0, [&](const auto& sum, const auto& x) {
            const auto num_tail = __builtin_popcount(x);
            return sum + min(num_tail, n - num_tail);
        });
    };
    int best_score = INT_MAX;
    for (double t = 1; t > LIM; t *= DELTA) {
        const auto e1 = minimize();
        if (e1 < best_score) best_score = e1;
        const auto bit = 1 << random_int(rng);
        for (auto& x : best) {
            x ^= bit;
        }
        const auto e2 = minimize();
        const auto p = exp((e1 - e2) / (k * t));
        if (p < random_double(rng)) {
            for (auto& x : best) {
                x ^= bit;
            }
        }
    }
    cout << best_score;
}