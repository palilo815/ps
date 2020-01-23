#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    int N, ans = 0;
    cin >> N;
    while (N--) {
        cin >> s;
        stack<char> stk;
        for (char c : s) {
            if (stk.empty() || stk.top() != c)
                stk.push(c);
            else
                stk.pop();
        }
        if (stk.empty()) ++ans;
    }
    cout << ans;
    return 0;
}