#include <bits/stdc++.h>
using namespace std;

struct T {
    uint64_t a, b;

    T() : a(0), b(0) {}
    T(uint64_t x) : a(x), b(0) {}
    T(uint64_t a, uint64_t b) : a(a), b(b) {}

    T conj() const { return T {a - b, -b}; }
    T operator-() const { return T {-a, -b}; }
};

const T OMEGA = {0, 1};
const T OMEGA2 = {-1ull, -1ull};
const T INV3 = {12297829382473034411ull, 0};

T operator+(const T& u, const T& v) {
    return {u.a + v.a, u.b + v.b};
}

T operator-(const T& u, const T& v) {
    return {u.a - v.a, u.b - v.b};
}

T operator*(const T& u, const T& v) {
    return {u.a * v.a - u.b * v.b, u.b * v.a + u.a * v.b - u.b * v.b};
}

void operator+=(T& u, const T& v) {
    u.a += v.a;
    u.b += v.b;
}

void operator-=(T& u, const T& v) {
    u.a -= v.a;
    u.b -= v.b;
}

void operator*=(T& u, const T& v) {
    uint64_t tmp = u.a;
    u.a = u.a * v.a - u.b * v.b;
    u.b = u.b * v.a + tmp * v.b - u.b * v.b;
}

class Conv64 {
public:
    vector<int64_t> multiply(const vector<int64_t>& p,
        const vector<int64_t>& q) {
        vector<uint64_t> pp(p.size()), qq(q.size());
        for (uint64_t i = 0; i < p.size(); ++i) {
            pp[i] = p[i];
        }
        for (uint64_t i = 0; i < q.size(); ++i) {
            qq[i] = q[i];
        }
        uint64_t s = 1;
        while (s < p.size() + q.size() - 1) {
            s *= 3;
        }
        pp.resize(s);
        qq.resize(s);
        vector<int64_t> res(s);
        multiply_cyclic_raw(pp.data(), qq.data(), pp.size(), (uint64_t*)res.data());
        res.resize(p.size() + q.size() - 1);
        return res;
    }

private:
    T* tmp;

    void twiddle(T* p, uint64_t m, uint64_t t, T* to) {
        if (t == 0 || t == 3 * m) {
            for (uint64_t j = 0; j < m; ++j) {
                to[j] = p[j];
            }
            return;
        }
        uint64_t tt;
        T mult = 1;
        if (t < m) {
            tt = t;
        } else if (t < 2 * m) {
            tt = t - m;
            mult = OMEGA;
        } else {
            tt = t - 2 * m;
            mult = OMEGA2;
        }
        for (uint64_t j = 0; j < tt; j++) {
            to[j] = p[m - tt + j] * OMEGA * mult;
        }
        for (uint64_t j = tt; j < m; j++) {
            to[j] = p[j - tt] * mult;
        }
    }
    void fftdif(T* p, uint64_t m, uint64_t r) {
        if (r == 1) return;
        uint64_t rr = r / 3;
        uint64_t pos1 = m * rr, pos2 = 2 * m * rr;
        for (uint64_t i = 0; i < rr; ++i) {
            for (uint64_t j = 0; j < m; ++j) {
                tmp[j] = p[i * m + j] + p[pos1 + i * m + j] + p[pos2 + i * m + j];
                tmp[m + j] = p[i * m + j] + OMEGA * p[pos1 + i * m + j] + OMEGA2 * p[pos2 + i * m + j];
                tmp[2 * m + j] = p[i * m + j] + OMEGA2 * p[pos1 + i * m + j] + OMEGA * p[pos2 + i * m + j];
                p[i * m + j] = tmp[j];
            }
            twiddle(tmp + m, m, 3 * i * m / r, p + pos1 + i * m);
            twiddle(tmp + 2 * m, m, 6 * i * m / r, p + pos2 + i * m);
        }
        fftdif(p, m, rr);
        fftdif(p + pos1, m, rr);
        fftdif(p + pos2, m, rr);
    }
    void fftdit(T* p, uint64_t m, uint64_t r) {
        if (r == 1) return;
        uint64_t rr = r / 3;
        uint64_t pos1 = m * rr, pos2 = 2 * m * rr;
        fftdit(p, m, rr);
        fftdit(p + pos1, m, rr);
        fftdit(p + pos2, m, rr);
        for (uint64_t i = 0; i < rr; ++i) {
            twiddle(p + pos1 + i * m, m, 3 * m - 3 * i * m / r, tmp + m);
            twiddle(p + pos2 + i * m, m, 3 * m - 6 * i * m / r, tmp + 2 * m);
            for (uint64_t j = 0; j < m; ++j) {
                tmp[j] = p[i * m + j];
                p[i * m + j] = tmp[j] + tmp[m + j] + tmp[2 * m + j];
                p[i * m + pos1 + j] = tmp[j] + OMEGA2 * tmp[m + j] + OMEGA * tmp[2 * m + j];
                p[i * m + pos2 + j] = tmp[j] + OMEGA * tmp[m + j] + OMEGA2 * tmp[2 * m + j];
            }
        }
    }
    void mul(T* p, T* q, uint64_t n, T* to) {
        if (n <= 27) {
            // O(n^2) grade-school multiplication
            for (uint64_t i = 0; i < n; ++i) {
                to[i] = 0;
            }
            for (uint64_t i = 0; i < n; ++i) {
                for (uint64_t j = 0; j < n - i; ++j) {
                    to[i + j] += p[i] * q[j];
                }
                for (uint64_t j = n - i; j < n; ++j) {
                    to[i + j - n] += p[i] * q[j] * OMEGA;
                }
            }
            return;
        }

        uint64_t m = 1;
        while (m * m < n) {
            m *= 3;
        }
        uint64_t r = n / m;

        T inv = 1;
        for (uint64_t i = 1; i < r; i *= 3) {
            inv *= INV3;
        }
        for (uint64_t i = 0; i < r; ++i) {
            twiddle(p + m * i, m, m / r * i, to + m * i);
            twiddle(q + m * i, m, m / r * i, to + n + m * i);
        }
        fftdif(to, m, r);
        fftdif(to + n, m, r);
        for (uint64_t i = 0; i < r; ++i) {
            mul(to + m * i, to + n + m * i, m, to + 2 * n + m * i);
        }
        fftdit(to + 2 * n, m, r);
        for (uint64_t i = 0; i < n; ++i) {
            to[2 * n + i] *= inv;
        }
        for (uint64_t i = 0; i < r; ++i) {
            twiddle(to + 2 * n + m * i, m, 3 * m - m / r * i, to + n + m * i);
        }

        for (uint64_t i = 0; i < r; ++i) {
            for (uint64_t j = 0; j < m; ++j) {
                p[m * i + j] = p[m * i + j].conj();
                q[m * i + j] = q[m * i + j].conj();
            }
            twiddle(p + m * i, m, 2 * m / r * i, to + m * i);
            twiddle(q + m * i, m, 2 * m / r * i, p + m * i);
        }

        fftdif(to, m, r);
        fftdif(p, m, r);
        for (uint64_t i = 0; i < r; ++i) {
            mul(to + m * i, p + m * i, m, to + 2 * n + m * i);
        }
        fftdit(to + 2 * n, m, r);
        for (uint64_t i = 0; i < n; ++i) {
            to[2 * n + i] *= inv;
        }

        for (uint64_t i = 0; i < r; ++i) {
            twiddle(to + 2 * n + m * i, m, 3 * m - 2 * m / r * i, q + m * i);
        }

        for (uint64_t i = 0; i < n; ++i) {
            to[i] = 0;
        }
        for (uint64_t i = 0; i < r; ++i) {
            for (uint64_t j = 0; j < m; ++j) {
                to[i * m + j] += (1 - OMEGA) * to[n + i * m + j] + (1 - OMEGA2) * q[i * m + j].conj();
                if (i * m + m + j < n) {
                    to[i * m + m + j] += (OMEGA2 - OMEGA) * (to[n + i * m + j] - q[i * m + j].conj());
                } else {
                    to[i * m + m + j - n] += (1 - OMEGA2) * (to[n + i * m + j] - q[i * m + j].conj());
                }
            }
        }
        for (uint64_t i = 0; i < n; ++i) {
            to[i] *= INV3;
        }
    }

    void multiply_cyclic_raw(uint64_t* p, uint64_t* q, uint64_t n,
        uint64_t* target) {
        uint64_t m = 1;
        while (m * m <= n) {
            m *= 3;
        }
        m /= 3;
        uint64_t r = n / m;

        T inv = 1;
        for (uint64_t i = 1; i < r; i *= 3) {
            inv *= INV3;
        }
        T* buf = new T[3 * n + 6 * m];
        T* pp = buf;
        T* qq = buf + n;
        T* to = buf + 2 * n;
        tmp = buf + 3 * n + 3 * m;

        for (uint64_t i = 0; i < n; ++i) {
            pp[i] = p[i];
            qq[i] = q[i];
        }

        fftdif(pp, m, r);
        fftdif(qq, m, r);
        for (uint64_t i = 0; i < r; ++i) {
            mul(pp + i * m, qq + i * m, m, to + i * m);
        }
        fftdit(to, m, r);
        for (uint64_t i = 0; i < n; ++i) {
            pp[i] = to[i] * inv;
        }

        for (uint64_t i = 0; i < n; ++i) to[i] = 0;
        for (uint64_t i = 0; i < r; ++i) {
            for (uint64_t j = 0; j < m; ++j) {
                to[i * m + j] += (1 - OMEGA) * pp[i * m + j] + (1 - OMEGA2) * pp[i * m + j].conj();
                if (i * m + m + j < n) {
                    to[i * m + m + j] += (OMEGA2 - OMEGA) * (pp[i * m + j] - pp[i * m + j].conj());
                } else {
                    to[i * m + m + j - n] += (OMEGA2 - OMEGA) * (pp[i * m + j] - pp[i * m + j].conj());
                }
            }
        }
        for (uint64_t i = 0; i < n; ++i) {
            target[i] = (to[i] * INV3).a;
        }
        delete[] buf;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<int64_t> a(n + 1), b(m + 1);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    auto res = Conv64().multiply(a, b);
    cout << accumulate(res.begin(), res.end(), 0ll, [&](const auto& sum, const auto& x) {
        return sum ^ x;
    });
}
