#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int total;
    cin >> total;

    constexpr array<int, 10> num = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
    for (int h = 0; h < 24; ++h)
        for (int m = 0; m < 60; ++m)
            if (num[h / 10] + num[h % 10] + num[m / 10] + num[m % 10] == total) {
                cout << setfill('0') << setw(2) << h
                     << ':'
                     << setfill('0') << setw(2) << m;
                return 0;
            }
    cout << "Impossible";
}