#include <bits/stdc++.h>
using namespace std;

class bit_array {
    using block_t = unsigned long long;

    const size_t size;
    vector<block_t> bit;
    vector<int> pref;

public:
    bit_array(size_t n) : size((n + 63) >> 6), bit(size), pref(size + 1) {}

    void build() {
        for (size_t i = 0; i != size; ++i) {
            pref[i + 1] = pref[i] + __builtin_popcountll(bit[i]);
        }
    }
    // set i-th bit to value
    void set(size_t i, bool value) {
        const auto block_id = i >> 6, bit_id = i & 63;
        bit[block_id] = (bit[block_id] & ~(static_cast<block_t>(1) << bit_id)) | (static_cast<block_t>(value) << bit_id);
    }
    // # of value in [0, r)
    size_t rank(size_t r, bool value) const {
        return value ? rank(r) : r - rank(r);
    }
    // # of value in [l, r)
    size_t rank(size_t l, size_t r, bool value) const {
        return value ? rank(r) - rank(l) : (r - l) - (rank(r) - rank(l));
    }

private:
    // # of true in [0, r)
    size_t rank(size_t r) const {
        return pref[r >> 6] + __builtin_popcountll(bit[r >> 6] & ((static_cast<block_t>(1) << (r & 63)) - 1));
    }
};

template <typename T>
class wavelet_matrix {
    const size_t size, height;
    vector<bit_array> bit_matrix;
    vector<int> mid_point;

public:
    wavelet_matrix(vector<T> v)
        : wavelet_matrix(move(v), 1 + __lg(*max_element(v.begin(), v.end()))) {}
    wavelet_matrix(vector<T> v, size_t height)
        : size(v.size()), height(height), bit_matrix(height, bit_array(size)),
          mid_point(height) {
        for (auto h = height; h--;) {
            for (size_t i = 0; i != size; ++i) {
                bit_matrix[h].set(i, v[i] >> h & 1);
            }
            bit_matrix[h].build();
            mid_point[h] = stable_partition(v.begin(), v.end(), [&](const auto& x) { return !(x >> h & 1); }) -
                           v.begin();
        }
    }
    // # of x in [l, r)
    size_t rank(size_t l, size_t r, T x) const {
        for (auto h = height; h--;) {
            shrink(l, r, h, x >> h & 1);
        }
        return r - l;
    }
    // # of values in [0, upper) in range [l, r)
    size_t range_freq(size_t l, size_t r, T upper) const {
        size_t ret = 0;
        for (auto h = height; h--;) {
            const bool value = upper >> h & 1;
            if (value) ret += bit_matrix[h].rank(l, r, false);
            shrink(l, r, h, value);
        }
        return ret;
    }
    // # of values in [lower, upper) in range [l, r)
    size_t range_freq(size_t l, size_t r, T lower, T upper) const {
        return range_freq(l, r, upper) - range_freq(l, r, lower);
    }
    // k-th (0-based) smallest value in [l, r)
    T kth_smallest(size_t l, size_t r, size_t k) const {
        size_t ret = 0;
        for (auto h = height; h--;) {
            const auto zeros = bit_matrix[h].rank(l, r, false);
            const auto value = zeros <= k;
            if (value) {
                ret |= static_cast<T>(1) << h;
                k -= zeros;
            }
            shrink(l, r, h, value);
        }
        return ret;
    }
    // k-th (0-based) largest value in [l, r)
    T kth_largest(size_t l, size_t r, size_t k) const {
        return kth_smallest(l, r, r - l - k - 1);
    }

private:
    void shrink(size_t& l, size_t& r, size_t h, bool value) const {
        l = bit_matrix[h].rank(l, value) + mid_point[h] * value;
        r = bit_matrix[h].rank(r, value) + mid_point[h] * value;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    int64_t k;
    cin >> n >> k;
    vector<int> vals(n);
    for (auto& x : vals) {
        cin >> x;
    }
    auto a = vals;
    ranges::sort(vals);
    for (auto& x : a) {
        x = ranges::lower_bound(vals, x) - vals.begin();
    }
    const auto wm = wavelet_matrix(a, 1 + __lg(n));
    for (int i = 0; i < n; ++i) {
        const auto cnt_larger = wm.range_freq(0, i, a[i], n);
        if (!cnt_larger) continue;
        if (k > cnt_larger + 1) {
            k -= cnt_larger + 1;
        } else {
            if (k == cnt_larger + 1) {
                sort(a.begin(), a.begin() + i + 1);
            } else {
                sort(a.begin(), a.begin() + i);
                copy(a.begin() + i - k, a.begin() + i, a.begin() + i - k + 1);
            }
            return ranges::transform(a, ostream_iterator<int>(cout, " "), [&](const auto& x) { return vals[x]; }), 0;
        }
    }
    cout << -1;
}
