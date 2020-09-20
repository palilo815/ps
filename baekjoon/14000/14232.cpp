#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    ll N;
    scanf("%lld", &N);

    ll tmp = N;
    vector<ll> ans;
    for (ll i = 2; i * i <= tmp; ++i)
        while (N % i == 0) {
            N /= i;
            ans.emplace_back(i);
        }
    if (N > 1) ans.emplace_back(N);

    printf("%d\n", ans.size());
    for (auto& x : ans) printf("%lld ", x);
    return 0;
}