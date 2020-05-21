#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll k; cin >> k;
    ll cnt = 1;

    vector<pair<ll, ll>> DP = { {1,1} };
    while (cnt < k) {
        auto [zero, one] = DP.back();
        DP.emplace_back(zero + one, zero);
        cnt += zero;
    }
    
    ++k;
    for (auto it = DP.rbegin(); it != DP.rend(); ++it) {
        if (k > it->first) {
            cout << 1;
            k -= it->first;
        }
        else cout << 0;
    }
    return 0;
}