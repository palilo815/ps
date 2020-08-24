#include <bits/stdc++.h>
using namespace std;

const int mxN = 50;

int a[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i];

    int S; cin >> S;
    for (int i = 0; i < N - 1 && S; ++i) {
        auto mx = max_element(a + i, a + min(i + S + 1, N));
        auto mx_val = *mx;
        copy(a + i, mx, a + i + 1);
        a[i] = mx_val;
        S -= mx - (a + i);
    }

    for (int i = 0; i < N; ++i)
        cout << a[i] << ' ';
    return 0;
}