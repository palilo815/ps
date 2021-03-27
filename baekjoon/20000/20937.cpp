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

    array<int, 50000> cnt {};
    for (int c; n--;) {
        cin >> c, --c;
        ++cnt[c];
    }
    cout << *max_element(cnt.begin(), cnt.end());
}