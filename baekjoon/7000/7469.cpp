#include <bits/stdc++.h>
using namespace std;

template <typename T, unsigned mxB>
struct wavelet_matrix {
    static constexpr size_t BLOCK_SIZE = 64;
    array<vector<uint64_t>, mxB> bit_array;
    array<vector<int>, mxB> psum;
    array<int, mxB> zeros;

    wavelet_matrix(vector<T>& a) {
        const size_t block_count = a.size() / BLOCK_SIZE + 1;
        vector<T> b(a.size());

        for (auto pos = mxB; pos--;) {
            bit_array[pos].resize(block_count);
            psum[pos].resize(block_count);

            int lo = 0, hi = a.size();
            for (size_t i = 0; i < a.size(); ++i) {
                if (a[i] & (T(1) << pos)) {
                    bit_array[pos][i / BLOCK_SIZE] |= 1ull << (i % BLOCK_SIZE);
                    b[--hi] = a[i];
                } else
                    b[lo++] = a[i];
            }

            for (size_t i = 1; i < block_count; ++i)
                psum[pos][i] = psum[pos][i - 1] + __builtin_popcountll(bit_array[pos][i - 1]);

            zeros[pos] = lo;
            reverse(b.begin() + hi, b.end());
            a.swap(b);
        }
    }
    int count_1(int i, int r) const {
        uint64_t mask = (1ull << (r % BLOCK_SIZE)) - 1;
        return psum[i][r / BLOCK_SIZE] + __builtin_popcountll(bit_array[i][r / BLOCK_SIZE] & mask);
    }
    T kth(int l, int r, int k) const {
        T ret = 0;
        for (auto pos = mxB; pos--;) {
            int lc = count_1(pos, l), rc = count_1(pos, r);
            int zero = (r - l) - (rc - lc);
            if (k >= zero) {
                ret |= T(1) << pos;
                l = lc + zeros[pos], r = rc + zeros[pos];
                k -= zero;
            } else
                l -= lc, r -= rc;
        }
        return ret;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, q;
    cin >> n >> q;

    constexpr int base = 1e9;

    vector<int> a(n);
    for (auto& x : a) cin >> x, x += base;

    wavelet_matrix<int, 31> wm(a);
    for (int l, r, k; q--;) {
        cin >> l >> r >> k;
        --l, --k;
        cout << wm.kth(l, r, k) - base << '\n';
    }
}