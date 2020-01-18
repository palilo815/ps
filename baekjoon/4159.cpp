#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n;
    while (cin >> n) {
        if (!n) break;
        vector<int> st(n + 1);
        loop(i, n) cin >> st[i];
        st[n] = 1422;
        sort(st.begin(), st.end());

        bool possible = true;
        loop(i,n)
            if (st[i + 1] - st[i] > 200) {
                possible = false;
                break;
            }
        if (possible) cout << "POSSIBLE\n";
        else cout << "IMPOSSIBLE\n";
    }
    return 0;
}