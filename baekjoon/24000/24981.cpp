#include <bits/stdc++.h>

int main() {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> le, ge;
    for (int _ {}; _ < n; ++_) {
        char dir;
        int loc;
        cin >> dir >> loc;
        (dir == 'L' ? le : ge).emplace_back(loc);
    }
    sort(le.begin(), le.end());
    sort(ge.begin(), ge.end(), greater());
    auto ans {INT_MAX};
    auto ge_liar {static_cast<int>(ge.size())};
    for (int le_liar {}; le_liar < static_cast<int>(le.size()); ++le_liar) {
        while (ge_liar && ge[ge_liar - 1] <= le[le_liar]) --ge_liar;
        ans = min(ans, le_liar + ge_liar);
    }
    cout << ans;
}
