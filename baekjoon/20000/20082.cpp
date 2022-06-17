#include "laugh.h"

int longest_laugh(std::string s) {
    auto is_laugh = [](auto const& x) { return x == 'a' || x == 'h'; };
    int ans {is_laugh(s[0])};
    for (int i {1}, now {ans}; i < static_cast<int>(s.size()); ++i) {
        if (!is_laugh(s[i])) {
            now = 0;
            continue;
        }
        if (s[i - 1] == s[i]) now = 0;
        ++now;
        if (now > ans) ans = now;
    }
    return ans;
}
