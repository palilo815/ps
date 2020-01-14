#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int height[500000], ans[500000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) cin >> height[i];

    stack<int> stk;
    loop(i, n) {
        int h = height[i];
        while (!stk.empty() && height[stk.top()] < h) stk.pop();

        if (stk.empty()) ans[i] = 0;
        else ans[i] = stk.top() + 1;
        stk.push(i);
    }
    loop(i, n) cout << ans[i] << ' ';
    return 0;
}