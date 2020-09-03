#include <bits/stdc++.h>
using namespace std;

const int mxN = 100;

int a[mxN];

int main() {
    int T, N; cin >> T >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i];

    sort(a, a + N);

    int i = 0;
    for (int s = 0; i < N; ++i)
        if ((s += a[i]) > T)
            break;
    cout << i;
    return 0;
}