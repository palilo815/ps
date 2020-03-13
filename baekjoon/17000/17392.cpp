#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        int x; cin >> x;
        sum += x + 1;
    }

    if (sum >= M) { cout << 0; return 0; }
    ++N;
    int cnt = M - sum;
    int a = cnt / N, A = N - (cnt % N);
    int b = a + 1, B = N - A;
    int tmp1 = 0, tmp2 = 0;
    for (int i = 1; i <= a; ++i)
        tmp1 += i * i;
    for (int i = 1; i <= b; ++i)
        tmp2 += i * i;
    cout << tmp1 * A + tmp2 * B;
    return 0;
}