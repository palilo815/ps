#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    string N; int K;
    cin >> N >> K;
    int len = N.size();

    set<string> st[2];
    st[0].insert(N);
    loop(k, K) {
        int u = k % 2, v = 1 - (k % 2);
        st[v].clear();
        for (string s : st[u])
            loop(i, len - 1) for (int j = i + 1; j < len; ++j)
            if (s[j] != '0' || i != 0) {
                swap(s[i], s[j]);
                st[v].insert(s);
                swap(s[i], s[j]);
            }
    }

    if (st[K % 2].empty()) cout << -1;
    else {
        auto ans = st[K % 2].end();
        cout << *(--ans);
    }
    return 0;
}