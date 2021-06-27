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

    auto sum = accumulate(a.begin(), a.end(), 0);

    for (const auto& x : a)
        if (x == sum - x)
            return cout << x, 0;
    cout << "BAD";
}