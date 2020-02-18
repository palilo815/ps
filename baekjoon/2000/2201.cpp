#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> p;

int main()
{
    vector<p> DP;
    DP.push_back({ 1,1 });
    ll k; cin >> k;
    ll cnt = 1;
    while (cnt < k) {
        auto [zero, one] = DP.back();
        DP.push_back({ zero + one, zero });
        cnt += zero;
    }
    
    ++k;
    for (int i = DP.size() - 1; i >= 0; --i) {
        auto [zero, one] = DP[i];
        if (k > zero) {
            cout << 1;
            k -= zero;
        }
        else cout << 0;
    }
    return 0;
}