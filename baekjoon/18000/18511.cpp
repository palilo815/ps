#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int N, ans;
vector<int> vt;
void solve(int num) {
    if (num > N) return;
    else ans = max(ans, num);
    for (int x : vt)
        solve(num * 10 + x);
    return;
}
int main() {
    int K; cin >> N >> K;
    vt.resize(K);
    loop(i, K) cin >> vt[i];
    solve(0);
    cout << ans;
    return 0;
}