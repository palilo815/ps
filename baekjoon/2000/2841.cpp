#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cin.tie(NULL);
    ios::sync_with_stdio(false);

    vector<stack<int>> vt(7);
    int N, P; cin >> N >> P;
    int ans = 0;
    while (N--) {
        int s, p; cin >> s >> p;
        while (!vt[s].empty() && vt[s].top() > p) {
            ++ans;
            vt[s].pop();
        }
        if (vt[s].empty() || vt[s].top() != p) {
            ++ans;
            vt[s].push(p);
        }
    }
    cout << ans;
    return 0;
}