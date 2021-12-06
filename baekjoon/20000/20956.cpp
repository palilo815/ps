#include <bits/stdc++.h>

int main() {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    stable_sort(id.begin(), id.end(), [&](const auto& lhs, const auto& rhs) {
        return a[lhs] > a[rhs];
    });
    bool fliped = false;
    for (auto it = id.begin(), ed = it; m; it = ed) {
        ed = find_if_not(it, id.end(), [&](const auto& x) {
            return a[*it] == a[x];
        });
        for (auto jt = ed; m && it != jt; --m) {
            if (fliped) {
                fliped ^= a[*--jt] % 7 == 0;
                cout << *jt + 1 << '\n';
            } else {
                fliped ^= a[*it] % 7 == 0;
                cout << *it++ + 1 << '\n';
            }
        }
    }
}

