#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    string s;
    cin >> n >> s;

    vector<bool> used(n);
    auto valid = [&](int mid) {
        fill(used.begin(), used.end(), false);
        for (int cnt = mid, pi = n - 1, po = INT_MAX; cnt--; --pi) {
            for (; ~pi && s[pi] != 'I'; --pi)
                ;
            if (pi == -1) return false;
            for (po = min(po - 1, pi - 1); ~po && s[po] != 'O'; --po)
                ;
            if (po == -1) return false;

            used[po] = used[pi] = true;
        }

        for (int i = 0, stk = 0, cnt = mid; i < n; ++i) {
            if (!used[i] && (s[i] == 'J' || s[i] == 'I'))
                ++stk;
            else if (used[i] && s[i] == 'O' && stk) {
                --stk;
                if (--cnt == 0) return true;
            }
        }
        return false;
    };

    int lo = 0, hi = n / 3;
    while (lo != hi) {
        int mid = (lo + hi + 1) >> 1;
        valid(mid) ? lo = mid : hi = mid - 1;
    }
    cout << lo;
}