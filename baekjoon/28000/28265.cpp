#include "colored_dealt.h"
#include <array>
#include <string>

std::string guess(int n) {
    constexpr std::array COLOUR = {'B', 'G', 'R'};
    auto s = std::string(n, 'B');
    auto r = std::string(n, 0);
    for (auto i = 0, prv = 3 * n; i < n; ++i) {
        s[i] = 'R';
        auto const cur = design(s);
        r[i] = COLOUR[prv - cur];
        prv = cur;
    }
    return r;
}
