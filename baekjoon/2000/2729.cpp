#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s1, s2;
    int T; cin >> T;
    while (T--) {
        cin >> s1 >> s2;
        stack<int> ans;
        int carry = 0;
        
        while(s1.size() && s2.size()) {
            int num = s1.back() + s2.back() - 2 * '0' + carry;
            ans.push(num % 2);
            carry = num / 2;
            s1.pop_back(), s2.pop_back();
        }
        while (s1.size()) {
            int num = s1.back() - '0' + carry;
            ans.push(num % 2);
            carry = num / 2;
            s1.pop_back();
        }
        while (s2.size()) {
            int num = s2.back() - '0' + carry;
            ans.push(num % 2);
            carry = num / 2;
            s2.pop_back();
        }
        ans.push(carry);
        while (!ans.empty() && ans.top() == 0) ans.pop();
        if (ans.empty()) ans.push(0);
        while (!ans.empty()) {
            cout << ans.top(); ans.pop();
        }
        cout << '\n';
    }
    return 0;
}