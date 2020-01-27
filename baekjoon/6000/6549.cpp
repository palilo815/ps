#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long
using namespace std;
const int max_N = 100000;

int h[max_N + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    while (1) {
        // ** initialize **
        int N; cin >> N;
        if (N == 0) break;
        loop(i, N) cin >> h[i];
        h[N] = 0;

        // stack에는 계산해야할 직사각형의 index가 들어있음.
        stack<int> stk;
        ll ans = 0;
        loop(i, N + 1) {
            // h[stack.top()] > h[i] : 가로막는 직사각형을 발견한 경우
            // h[stack.top()] == h[i]인 경우도 답에 영향을 끼치지 않으나, stack자리를 차지하므로 계산해버리자
            while (!stk.empty() && h[stk.top()] > h[i]) {
                ll height = h[stk.top()]; stk.pop();
                ll L_most = stk.empty() ? -1 : stk.top();
                ans = max(ans, height * (i - L_most - 1));
            }
            stk.push(i);
        }
        cout << ans << '\n';
    }
    return 0;
}