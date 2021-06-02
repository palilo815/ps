#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n;
    cin >> n;

    vector<int> a(n), dwarves(n), elves(n);
    for (auto& x : a) cin >> x, --x;
    for (auto& x : dwarves) cin >> x;
    for (auto& x : elves) cin >> x;

    // simple greedy
    if (all_of(a.begin(), a.end(), [&](auto& x) { return x == a.front(); })) {
        sort(dwarves.begin(), dwarves.end(), greater<int>());
        sort(elves.begin(), elves.end(), greater<int>());

        int strong = 0, weak = n - 1;
        for (const auto& dwarf : dwarves)
            elves[strong] > dwarf ? ++strong : --weak;
        return cout << strong, 0;
    }

    vector<pair<int, int>> sorted_a(n);
    for (int i = 0; i < n; ++i)
        sorted_a[i] = {a[i], i};

    sort(sorted_a.begin(), sorted_a.end(), [&](auto& lhs, auto& rhs) {
        return lhs.first < rhs.first;
    });

    vector<pair<int, int>> intervals;
    for (int i = 0, j; i < n; i = j) {
        // [st, ed)
        int st = sorted_a[i].first, ed = st + 1;
        for (j = i + 1; j < n && sorted_a[j].first < ed; ++j)
            ++ed;
        intervals.emplace_back(st, ed);
    }

    intervals.back().second %= n;
    intervals.insert(intervals.begin(), intervals.back());
    intervals.pop_back();
    {
        auto& [st, ed] = intervals.front();
        auto it = intervals.begin() + 1;
        for (; it != intervals.end() && it->first < ed; ++it)
            ed += it->second - it->first;
        intervals.erase(intervals.begin() + 1, it);
    }

    int ptr = lower_bound(sorted_a.begin(), sorted_a.end(), pair(intervals.front().first, INT_MIN)) - sorted_a.begin();
    int win = 0;
    set<int> elf_power;
    for (const auto& [st, ed] : intervals) {
        assert(elf_power.empty());
        bool is_first = true;
        for (int pos = st; is_first || pos != ed; is_first = false, pos = (pos == n - 1 ? 0 : pos + 1)) {
            for (; sorted_a[ptr].first == pos; ptr = (ptr == n - 1 ? 0 : ptr + 1))
                elf_power.emplace(elves[sorted_a[ptr].second]);
            if (auto it = elf_power.upper_bound(dwarves[pos]); it == elf_power.end())
                elf_power.erase(elf_power.begin());
            else
                ++win, elf_power.erase(it);
        }
    }
    cout << win;
}