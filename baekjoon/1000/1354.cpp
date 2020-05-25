#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

unordered_map<ll, ll> cache(2000000);

int P, Q, X, Y;
ll solve(ll n) {
    if (n <= 0) return 1;
    if (cache[n]) return cache[n];
    return cache[n] = solve(n / P - X) + solve(n / Q - Y);
}
int main() {
    ll N;
    cin >> N >> P >> Q >> X >> Y;
    cout << solve(N);
    return 0;
}