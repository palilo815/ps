#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 200000;
const int max_X = 400001;
const int mod = 1000000007;

p star[max_N];
int fenwick[max_X + 1];

void update(int i) {
    while (i <= max_X) {
        ++fenwick[i];
        i += i & -i;
    }
}
int read(int i) {
    int ret = 0;
    while (i) {
        ret += fenwick[i];
        i -= i & -i;
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> star[i].second >> star[i].first;
    sort(star, star + N, greater<p>());

    stack<int> stk;
    int ans = 0, prv = INT_MIN;
    for (int i = 0; i < N; ++i) {
        auto [y, x] = star[i];
        x += max_N + 1;
        
        if (prv != y) while (!stk.empty()) {
            update(stk.top()); stk.pop();
        }
        stk.emplace(x);
        prv = y;

        ans += (long long)read(x - 1) * (read(max_X) - read(x)) % mod;
        ans %= mod;
    }
    cout << ans;
    return 0;
}