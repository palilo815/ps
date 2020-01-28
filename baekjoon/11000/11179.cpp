#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    stack<int> stk;
    int n, D = 1, ans = 0;
    cin >> n;
    while (n) {
        stk.push(n % 2);
        n /= 2;
    }
    while (!stk.empty()) {
        ans += stk.top() * D;
        D *= 2;
        stk.pop();
    }
    cout << ans;
    return 0;
}