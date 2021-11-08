#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    size_t n;
    cin >> n;
    vector<int> colour(n + 1);
    int c = 0;
    colour[1] = ++c;
    for (size_t i = 2; i <= n; ++i) {
        if (!colour[i]) {
            colour[i] = ++c;
            for (size_t j = i * i; j <= n; j += i) {
                colour[j] = c;
            }
        }
    }
    cout << c << '\n';
    for (size_t i = 1; i <= n; ++i) {
        cout << colour[i] << ' ';
    }
}