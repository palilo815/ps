#include <bits/stdc++.h>
using namespace std;

const int max_N = 100000;

int N;
int arr[max_N];
int odd[max_N + 1];
int even[max_N + 1];

int read(int fenwick[], int idx)
{
    int ret = 0;
    while (idx) {
        ret += fenwick[idx];
        idx -= (idx & -idx);
    }
    return ret;
}
void update(int fenwick[], int idx, int val)
{
    while (idx <= N) {
        fenwick[idx] += val;
        idx += (idx & -idx);
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> N;
    for (int i = 0; i < N; ++i) {
        int x; cin >> x;
        x %= 2;
        arr[i] = x;
        int* fenwick = (x ? odd : even);
        update(fenwick, i + 1, 1);
    }

    int Q; cin >> Q;
    while (Q--) {
        int q, a, b; cin >> q >> a >> b;
        if (q == 1) {
            b %= 2;
            if (arr[a - 1] != b) {
                arr[a - 1] = b;
                int* add = (b ? odd : even);
                int* sub = (b ? even : odd);
                update(add, a, 1);
                update(sub, a, -1);
            }
        }
        else {
            int* fenwick = (q == 2 ? even : odd);
            cout << read(fenwick, b) - read(fenwick, a - 1) << '\n';
        }
    }
    return 0;
}