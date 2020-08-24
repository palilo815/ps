#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 1000;

char mat[mx][mx];
unordered_set<string> st;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int R, C; cin >> R >> C;
    loop(i, R) loop(j, C) cin >> mat[i][j];

    int lo = 0, hi = R, ans;
    while (lo ^ hi) {
        st.clear();
        int m = (lo + hi) >> 1;

        bool dup = false;
        loop(j, C) {
            string s = "";
            for (int i = m; i < R; ++i)
                s += mat[i][j];
            if (st.count(s)) {
                dup = true;
                break;
            }
            st.emplace(s);
        }
        dup ? (hi = m) : (ans = m, lo = m + 1);
    }
    cout << ans;
    return 0;
}