#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int64_t n;
    cin >> n;

    vector<int64_t> prime;
    for (int64_t i = 2; i * i <= n; ++i)
        while (n % i == 0) {
            prime.emplace_back(i);
            n /= i;
        }
    if (n != 1) prime.emplace_back(n);

    if (prime.size() == 1) return cout << -1, 0;

    if (prime.size() & 1) {
        prime.end()[-2] *= prime.back();
        prime.pop_back();
    }
    for (int i = 0; i < int(prime.size()); i += 2)
        cout << prime[i] * prime[i + 1] << ' ';
}