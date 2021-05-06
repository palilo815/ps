#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<int> price(n);
    for (auto& x : price) cin >> x;

    constexpr int64_t mx_stock = 1e5;

    int64_t stock = 0, money = 100;

    for (int i = 0; i < n - 1; ++i) {
        money += exchange(stock, 0) * price[i];
        if (price[i] < price[i + 1]) {
            auto buy = min(mx_stock, money / price[i]);
            stock += buy;
            money -= buy * price[i];
        }
    }
    cout << money + stock * price.back();
}