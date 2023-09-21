#include <bits/stdc++.h>

class XSR128Plus {
  public:
    explicit XSR128Plus() : s({size_t(new size_t), size_t(new size_t)}) {}

    auto next() -> size_t {
        const auto s0 = s[0];
        auto s1 = s[1];
        const auto result = s0 + s1;
        s1 ^= s0;
        s[0] = rotl(s0, 24) ^ s1 ^ (s1 << 16);
        s[1] = rotl(s1, 37);
        return result;
    }

  private:
    std::array<size_t, 2> s;

    inline auto rotl(const size_t x, int k) -> size_t {
        return (x << k) | (x >> (64 - k));
    }
} xsr;

using iter_t = std::vector<int>::iterator;

auto partition(iter_t start, iter_t end) -> std::pair<iter_t, iter_t> {
    if (start + 1 == end) return {start, end};
    std::iter_swap(--end, start + xsr.next() % std::distance(start, end));
    auto lt = start;
    auto eq = start;
    for (auto i = start; i != end; ++i) {
        if (*i < *end) {
            std::iter_swap(i, eq);
            std::iter_swap(lt++, eq++);
        } else if (*i == *end) {
            std::iter_swap(i, eq++);
        }
    }
    return {lt, eq};
}

auto kth(std::vector<int> &a, int k) -> int {
    --k;
    for (auto s = a.begin(), e = a.end();;) {
        const auto [p1, p2] = partition(s, e);
        const auto num_less = std::distance(s, p1);
        const auto num_less_or_equal = std::distance(s, p2);
        if (k < num_less) {
            e = p1;
        } else if (k < num_less_or_equal) {
            return *p1;
        } else {
            k -= num_less_or_equal;
            s = p2;
        }
    }
}
