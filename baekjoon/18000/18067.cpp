#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int a, b, n;
    cin >> a >> b >> n;
    const int b_move = (n - b + b - a - 1) / (b - a);
    const int a_move = b_move + 1;
    cout << a_move + b_move;
}