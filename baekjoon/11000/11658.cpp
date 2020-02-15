#include <iostream>
using namespace std;

const int max_N = 1024;

int N;
int arr[max_N][max_N];
int fenwick[max_N + 1][max_N + 1];

void update(int r, int c, int val)
{
    for (int i = r; i <= N; i += i & -i)
        for (int j = c; j <= N; j += j & -j)
            fenwick[i][j] += val;
}
int read(int r, int c)
{
    int ret = 0;
    for (int i = r; i; i -= i & -i)
        for (int j = c; j; j -= j & -j)
            ret += fenwick[i][j];
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int Q; cin >> N >> Q;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            cin >> arr[i][j];
            update(i + 1, j + 1, arr[i][j]);
        }

    while (Q--) {
        int q, a, b, c; cin >> q >> a >> b >> c;
        if (q) {
            int d; cin >> d;
            cout << read(c, d) - read(c, b - 1) - read(a - 1, d) + read(a - 1, b - 1) << '\n';
        }
        else {
            int val = c - arr[a - 1][b - 1];
            arr[a - 1][b - 1] = c;
            update(a, b, val);
        }
    }
    return 0;
}