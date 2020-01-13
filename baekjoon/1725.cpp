#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int h[100001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> h[i];

    stack<int> stk;
    int ans = 0;
    loop(i, N + 1) {
        while (!stk.empty() && h[stk.top()] >= h[i]) {
            int height = h[stk.top()]; stk.pop();

            int L_most = -1;
            if (!stk.empty())
                L_most = stk.top();

            ans = max(ans, height * (i - L_most - 1));
        }
        stk.push(i);
    }
    cout << ans;
    return 0;
}