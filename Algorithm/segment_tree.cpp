/*
 * https://codeforces.com/blog/entry/18051
 * author: Al.Cash
*/
#include <bits/stdc++.h> 
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 100;

struct segT_simple {
    int N;
    int segT[max_N * 2];

    void init() {
        cin >> N;
        for (int i = N; i < N << 1; ++i)
            cin >> segT[i];
        for (int i = N - 1; i; --i)
            segT[i] = segT[i << 1] + segT[i << 1 | 1];
    }

    // arr[p] = v
    void modify(int p, int v) {
        for (segT[p += N] = v; p > 1; p >>= 1)
            segT[p >> 1] = segT[p] + segT[p ^ 1];
    }

    // return sum[l,r)
    int query(int l, int r) {
        int ret = 0;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ret += segT[l++];
            if (r & 1) ret += segT[--r];
        }
        return ret;
    }
};

struct segT_likeFenwick {
    int N;
    int segT[max_N * 2];

    void init() {
        cin >> N;
        for (int i = N; i < N << 1; ++i)
            cin >> segT[i];
        for (int i = N - 1; i; --i)
            segT[i] = segT[i << 1] + segT[i << 1 | 1];
    }

    void modify(int l, int r, int v) {
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) segT[l++] += v;
            if (r & 1) segT[--r] += v;
        }
    }

    int query(int p) {
        int ret = 0;
        for (p += N; p; p >>= 1)
            ret += segT[p];
        return ret;
    }
};

struct lazy_maxQuery {
    int N, h;
    int segT[max_N * 2];
    int lazy[max_N];

    void init() {
        cin >> N;
        for (int i = N; i < N << 1; ++i)
            cin >> segT[i];
        for (int i = N - 1; i; --i)
            segT[i] = segT[i << 1] + segT[i << 1 | 1];
        h = 32 - __builtin_clz(N);
    }

    void apply(int p, int v) {
        segT[p] += v;
        if (p < N) lazy[p] += v;
    }

    // update all the parents
    void build(int p) {
        while (p > 1)
            p >>= 1,
            segT[p] = max(segT[p << 1], segT[p << 1 | 1]) + lazy[p];
    }

    // propagate changes from all the parents to leaves
    void push(int p) {
        for (int s = h; s; --s) {
            int i = p >> s;
            if (lazy[i]) {
                apply(i << 1, lazy[i]);
                apply(i << 1 | 1, lazy[i]);
                lazy[i] = 0;
            }
        }
    }

    void inc(int l, int r, int v) {
        l += N, r += N;
        int l0 = l, r0 = r;
        while (l < r) {
            if (l & 1) apply(l++, v);
            if (r & 1) apply(--r, v);
            l >>= 1, r >>= 1;
        }
        build(l0);
        build(r0 - 1);
    }

    int query(int l, int r) {
        l += N, r += N;
        push(l);
        push(r - 1);

        int ret = INT_MIN;
        while (l < r) {
            if (l & 1) ret = max(ret, segT[l++]);
            if (r & 1) ret = max(ret, segT[--r]);
            l >>= 1, r >>= 1;
        }
        return ret;
    }
};

struct lazy_sumQuery {
    int N, h;
    int segT[max_N * 2];
    int lazy[max_N];

    void init() {
        cin >> N;
        for (int i = N; i < N << 1; ++i)
            cin >> segT[i];
        for (int i = N - 1; i; --i)
            segT[i] = segT[i << 1] + segT[i << 1 | 1];
        h = 32 - __builtin_clz(N);
        memset(lazy, 0, sizeof(lazy));
    }

    // k = lenght of interval
    void calc(int p, int k) {
        if (lazy[p]) segT[p] = lazy[p] * k;
        else segT[p] = segT[p << 1] + segT[p << 1 | 1];
    }
    
    void apply(int p, int v, int k) {
        segT[p] = v * k;
        if (p < N) lazy[p] = v;
    }

    void build(int l, int r) {
        int k = 2;
        for (l += N, r += N - 1; l > 1; k <<= 1) {
            l >>= 1, r >>= 1;
            for (int i = r; i >= l; --i) calc(i, k);
        }
    }

    void push(int l, int r) {
        int s = h, k = 1 << (h - 1);
        for (l += N, r += N - 1; s; --s, k >>= 1)
            for (int i = l >> s; i <= r >> s; ++i) if (lazy[i]) {
                apply(i << 1, lazy[i], k);
                apply(i << 1 | 1, lazy[i], k);
                lazy[i] = 0;
            }
    }

    void modify(int l, int r, int v) {
        if (v == 0) return;
        push(l, l + 1);
        push(r - 1, r);
        /*int l0 = l, r0 = r, k = 1;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1, k <<= 1) {
            if (l & 1) apply(l++, v, k);
            if (r & 1) apply(--r, v, k);
        }
        build(l0, l0 + 1);
        build(r0 - 1, r0);*/
        bool cl = false, cr = false;
        int k = 1;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1, k <<= 1) {
            if (cl) calc(l - 1, k);
            if (cr) calc(r, k);
            if (l & 1) apply(l++, v, k), cl = true;
            if (r & 1) apply(--r, v, k), cr = true;
        }
        for (--l; r; l >>= 1, r >>= 1, k <<= 1) {
            if (cl) calc(l, k);
            if (cr && (!cl || l != r)) calc(r, k);
        }
    }

    int query(int l, int r) {
        push(l, l + 1);
        push(r - 1, r);
        int ret = 0;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ret += segT[l++];
            if (r & 1) ret += segT[--r];
        }
        return ret;
    }
};
int main() {
    lazy_sumQuery t;
    t.init();
    while (1) {
        int q; cin >> q;
        if (q == 1) {
            int l, r, v; cin >> l >> r >> v;
            t.modify(l, r, v);
        }
        else if (q == 2) {
            int l, r; cin >> l >> r;
            cout << t.query(l, r);
        }
        else break;
    }
    return 0;
}