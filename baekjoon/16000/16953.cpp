#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;

int main()
{
    int a, b; cin >> a >> b;
    queue<int> q;
    q.push(a); q.push(-1);
    int ans = 1;
    while (1) {
        int num = q.front(); q.pop();
        if (num == b) break;
        if (num == -1) {
            if (q.empty()) { ans = -1; break; }
            ++ans; q.push(-1);
            continue;
        }
        ll tmp = num * 2;
        if (tmp <= b) q.push(tmp);
        tmp = num * 10 + 1;
        if (tmp <= b) q.push(tmp);
    }
    cout << ans;
    return 0;
}