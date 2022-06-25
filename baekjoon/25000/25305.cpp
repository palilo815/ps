#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, k;
    cin >> n >> k, --k;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    nth_element(a.begin(), a.begin() + k, a.end(), greater());
    cout << a[k];
}
