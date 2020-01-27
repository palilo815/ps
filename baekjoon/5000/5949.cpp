#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL); cout.tie(NULL);
    ios::sync_with_stdio(false);

    stack<char> ans;
    string s; cin >> s;
    int len =  s.size();
    loop(i, len) {
        ans.push(s[len - 1 - i]);
        if (i % 3 == 2) ans.push(',');
    }
    if (ans.top() == ',') ans.pop();
    while (!ans.empty()) {
        cout << ans.top();
        ans.pop();
    }
    return 0;
}