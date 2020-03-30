#include <bits/stdc++.h>
using namespace std;

int A[15];
int N, L, R, X;

bool is_ok(int mask) {
    int _min = -1, _max = 0, _sum = 0;
    for (int i = 0; mask; ++i, mask >>= 1)
        if (mask & 1) {
            _sum += A[i];
            _max = A[i];
            if (_min == -1) _min = A[i];
        }
    return _max - _min >= X && _sum >= L && _sum <= R;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> N >> L >> R >> X;
    for (int i = 0; i < N; ++i)
        cin >> A[i];
    sort(A, A + N);

    int ans = 0;
    for (int i = 1; i < (1 << N); ++i)
        if (is_ok(i)) ++ans;
    cout << ans;
    return 0;
}