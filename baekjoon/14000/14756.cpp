#include <bits/stdc++.h>
using namespace std;

constexpr double PI = acos(-1.0);

namespace FFT {
void fft(vector<complex<double>>& a) {
    const int n = a.size(), L = __lg(n);
    static vector<complex<double>> R(2, 1);
    static vector<complex<double>> rt(2, 1);

    for (static int k = 2; k < n; k <<= 1) {
        R.resize(n), rt.resize(n);
        const auto x = polar(1.0, PI / k);
        for (int i = k; i < k << 1; ++i)
            rt[i] = R[i] = i & 1 ? R[i >> 1] * x : R[i >> 1];
    }

    vector<int> rev(n);
    for (int i = 0; i < n; ++i)
        rev[i] = (rev[i >> 1] | (i & 1) << L) >> 1;
    for (int i = 0; i < n; ++i)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);

    for (int k = 1; k < n; k <<= 1)
        for (int i = 0; i < n; i += k << 1)
            for (int j = 0; j < k; ++j) {
                const auto z = rt[j + k] * a[i + j + k];
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
}
vector<int64_t> conv(const vector<int64_t>& a, const vector<int64_t>& b) {
    if (a.empty() || b.empty()) return {};
    vector<int64_t> res(a.size() + b.size() - 1);
    const int L = __lg(res.size()) + 1, n = 1 << L;

    vector<complex<double>> in(n);
    copy(a.begin(), a.end(), in.begin());
    for (int i = 0; i < int(b.size()); ++i)
        in[i].imag(b[i]);

    fft(in);
    for (auto& x : in) x *= x;

    vector<complex<double>> out(n);
    for (int i = 0; i < n; ++i)
        out[i] = in[-i & (n - 1)] - conj(in[i]);

    fft(out);
    for (int i = 0; i < int(res.size()); ++i)
        res[i] = llround(imag(out[i])) / (n << 2);
    return res;
}
}; // namespace FFT

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int m, l, n;
    int64_t w;
    cin >> m >> l >> n >> w;

    vector<vector<int64_t>> path(n, vector<int64_t>(m));
    for (auto& v : path)
        for (auto& x : v)
            cin >> x;

    vector<vector<int64_t>> tele(n, vector<int64_t>(l));
    for (auto& v : tele)
        for (int i = l; i--;)
            cin >> v[i];

    vector<int64_t> light(m - l + 1);
    for (int i = 0; i < n; ++i) {
        auto res = FFT::conv(path[i], tele[i]);
        for (int i = 0; i < int(light.size()); ++i)
            light[i] += res[i + l - 1];
    }
    cout << count_if(light.begin(), light.end(), [&](auto& x) {
        return x > w;
    });
}