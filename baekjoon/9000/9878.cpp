#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e4;

int a[mxN + 1], b[mxN + 2];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    int A = 0, B = 0;
    for (int x; N; --N) {
        char c; cin >> c >> x;
        (c == 'T' ? a[A++] : b[B++]) = x;
    }

    sort(a, a + A);
    sort(b, b + B);

    b[B++] = 1000;
    a[A] = b[B] = INT_MAX;

    double t = 0, d = 0;
    for (int i = 0, j = 0, div = 1; i ^ A || j ^ B; ++div) {
        double to_i = a[i] - t, to_j = b[j] - d;

        if (to_i < to_j * div)
            t = a[i++], d += to_i / div;
        else
            d = b[j++], t += to_j * div;
    }
    cout << (long long)(t + 0.5);
    return 0;
}