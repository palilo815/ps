#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    set<string> st;
    string s1, s2, ans = "";
    int T; cin >> T;
    while (T-- && ans == "") {
        cin >> s1;
        s2 = s1;
        reverse(s1.begin(), s1.end());
        if (s1.compare(s2) == 0) ans = s1;
        else if (s1.compare(s2) > 0) s1 = s2;
        if (st.find(s1) == st.end())
            st.insert(s1);
        else ans = s1;
    }
    cout << ans.length() << '\n' << ans[ans.length() / 2];
    return 0;
}