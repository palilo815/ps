#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
#define success    \
    do {           \
        cout << 1; \
        return 0;  \
    } while (0)
using namespace std;

const int mxN = 5e3;

int a[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, C;
    cin >> N >> C;
    loop(i, N) cin >> a[i];

    sort(a, a + N);
    if (binary_search(a, a + N, C))
        success;

    for (int l = 0, r = N - 1, s; l ^ r;) {
        if ((s = a[l] + a[r]) == C)
            success;
        if (s < C) {
            if (C - s != a[l] && C - s != a[r] && binary_search(a, a + N, C - s))
                success;
            ++l;
        } else
            --r;
    }
    cout << 0;
    return 0;
}