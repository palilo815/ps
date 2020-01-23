#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t = 0, n;
    while (1) {
        cin >> n; cin.ignore();
        if (n == 0) break;
        set<string> st;
        while (n--) {
            string s;
            getline(cin, s);
            if (st.find(s) == st.end())
                st.insert(s);
        }
        cout << "Week " << ++t << ' ' << st.size() << '\n';
    }
    return 0;
}