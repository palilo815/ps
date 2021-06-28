#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n;
    cin >> n;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    vector<int> stk;
    stk.reserve(n);

    int ans = 0;
    for (const auto& x : a) {
        while (!stk.empty() && stk.back() < x) {
            ++ans;
            stk.pop_back();
        }
        stk.emplace_back(x);
    }

    reverse(a.begin(), a.end());
    stk.clear();

    for (const auto& x : a) {
        while (!stk.empty() && stk.back() < x) {
            ++ans;
            stk.pop_back();
        }
        stk.emplace_back(x);
    }
    cout << ans;
}