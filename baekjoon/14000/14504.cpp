#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 1e5;
const int mxsq = 317;

int sq, a[mxN];
int bucket[mxsq][mxsq];

void update(int bucket[], int v_old, int v_new) {
    int* p_old = lower_bound(bucket, bucket + sq, v_old), * p_new;
    if (v_new < v_old) {
        p_new = lower_bound(bucket, bucket + sq, v_new);
        copy(p_new, p_old, p_new + 1);
    }
    else {
        p_new = upper_bound(bucket, bucket + sq, v_new) - 1;
        copy(p_old + 1, p_new + 1, p_old);
    }
    *p_new = v_new;
}
int query(int i, int j, int k) {
    int ret = 0, b1 = (i - 1) / sq + 1, b2 = j / sq;
    if (b1 > b2) {
        for (; i < j; ++i) ret += a[i] > k;
        return ret;
    }

    for (; i < b1 * sq; ++i)
        ret += a[i] > k;
    for (; b1 < b2; ++b1)
        ret += bucket[b1] + sq - upper_bound(bucket[b1], bucket[b1] + sq, k);
    for (i = b2 * sq; i < j; ++i)
        ret += a[i] > k;
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> a[i];

    sq = sqrt(N - 1) + 1;
    loop(i, N / sq) {
        copy(a + i * sq, a + (i + 1) *sq, bucket[i]);
        sort(bucket[i], bucket[i] + sq);
    }
    if (N % sq) {
        copy(a + N / sq * sq, a + N, bucket[N / sq]);
        sort(bucket[N / sq], bucket[N / sq] + sq);
    }

    int Q; cin >> Q;
    for (int q, i, j, k; Q--;) {
        cin >> q;
        if (q == 1) {
            cin >> i >> j >> k; --i;
            cout << query(i, j, k) << '\n';
        }
        else {
            cin >> i >> k; --i;
            update(bucket[i / sq], a[i], k);
            a[i] = k;
        }
    }
    return 0;
}