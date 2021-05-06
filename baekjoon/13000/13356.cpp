#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

struct _card {
    int rank, suit;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<_card> card(n);
    for (auto& [rank, suit] : card) {
        char buf[3];
        cin >> buf;
        if (isdigit(buf[0])) rank = buf[0] - '0';
        else {
            switch (buf[0]) {
            case 'T': rank = 10; break;
            case 'J': rank = 11; break;
            case 'Q': rank = 12; break;
            case 'K': rank = 13; break;
            case 'A': rank = 14; break;
            default: assert(false);
            }
        }
        switch (buf[1]) {
        case 's': suit = 0; break;
        case 'h': suit = 1; break;
        case 'd': suit = 2; break;
        case 'c': suit = 3; break;
        default: assert(false);
        }
    }

    vector<int> id(n);
    iota(id.begin(), id.end(), 0);

    auto lis = [&]() -> int {
        vector<int> dp;
        for (const auto& x : id)
            if (auto it = lower_bound(dp.begin(), dp.end(), x); it == dp.end())
                dp.emplace_back(x);
            else
                *it = x;
        return dp.size();
    };

    int max_lis = -1;
    array suit_ord = {0, 1, 2, 3};
    do {
        for (int ascending = 0; ascending < 16; ++ascending) {
            sort(id.begin(), id.end(), [&](auto& a, auto& b) {
                const auto& [rank_a, suit_a] = card[a];
                const auto& [rank_b, suit_b] = card[b];

                if (suit_a != suit_b)
                    return suit_ord[suit_a] < suit_ord[suit_b];
                return ascending >> suit_a & 1 ? (rank_a < rank_b) : (rank_a > rank_b);
            });
            chmax(max_lis, lis());
        }
    } while (next_permutation(suit_ord.begin(), suit_ord.end()));
    cout << n - max_lis;
}