#include <bits/stdc++.h>
using namespace std;

struct elem {
    int id, bsum, csum;
    elem(int id, int bsum, int csum) : id(id), bsum(bsum), csum(csum) {}
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    string s;
    cin >> n >> k >> s;

    vector<elem> stk;
    stk.emplace_back(-1, 0, 0);

    vector<vector<int>> ans;
    ans.reserve(n / (k + 1));

    for (int i = 0; i < n; ++i) {
        stk.emplace_back(i, stk.back().bsum + (s[i] == 'b'), stk.back().csum + (s[i] == 'c'));
        if (stk.size() > k + 1 &&
            stk.back().bsum - stk.end()[-k - 2].bsum == k &&
            stk.back().csum - stk.end()[-k - 2].csum == 1) {
            vector<int> vt(k + 1);
            for (int i = 0; i < k + 1; ++i)
                vt[i] = stk.end()[i - k - 1].id + 1;

            stk.erase(stk.end() - k - 1, stk.end());
            ans.emplace_back(vt);
        }
    }

    reverse(ans.begin(), ans.end());
    for (const auto& vt : ans) {
        for (const auto& x : vt) cout << x << ' ';
        cout << '\n';
    }
}