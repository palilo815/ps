#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        set<int> st;
        int N; cin >> N;
        while (N--) {
            int x; cin >> x;
            st.insert(x);
        }
        cin >> N;
        while (N--) {
            int x; cin >> x;
            if (st.find(x) == st.end())
                cout << 0 << '\n';
            else cout << 1 << '\n';
        }
    }
    return 0;
}