#include <bits/stdc++.h>
using namespace std;

int a[9];

void solve() {
    for (int i = 0; i < 9; ++i)
        cin >> a[i];
    sort(a, a + 9);

    int s = accumulate(a, a + 9, 0);
    for (int i = 0; i < 9; ++i)
        for (int j = i + 1; j < 9; ++j)
            if (a[i] + a[j] == s - 100) {
                a[i] = a[j] = -1;
                return;
            }
}
int main() {
    solve();
    for (int i = 0; i < 9; ++i)
        if (~a[i]) cout << a[i] << '\n';
    return 0;
}