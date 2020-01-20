#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, b; cin >> n >> b;
    stack<int> ans;
    while (n) {
        ans.push(n % b);
        n /= b;
    }
    while (!ans.empty()) {
        int x = ans.top();
        ans.pop();
        if (x < 10) cout << x;
        else cout << (char)('A' + x - 10);
    }
    return 0;
}