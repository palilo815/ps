#include <bits/stdc++.h>
using namespace std;

int main() {
    double x, y; cin >> x >> y;
    if (x > y) swap(x, y);
    cout << fixed << setprecision(9)
         << max(x / 2, min(y / 3, x));
    return 0;
}