#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 1000000;

// cnt : 해당 숫자가 얼마나 나왔는지
// num : 수열 (이후에 정답 저장용으로 재사용)
int cnt[max_N + 1], num[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) {
        cin >> num[i];
        ++cnt[num[i]];
    }
    stack<int> stk;
    for (int i = N - 1; i >= 0; --i) {
        int n = num[i];
        while (!stk.empty() && cnt[stk.top()] <= cnt[n])
            stk.pop();
        if (stk.empty()) num[i] = -1;
        else num[i] = stk.top();
        stk.push(n);
    }
    loop(i, N) cout << num[i] << ' ';
    return 0;
}