#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool visited[100001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, k; cin >> n >> k;

    queue<int> q;
    q.push(n), q.push(-1);
    int ans = 0;
    while (1) {
        int x = q.front(); q.pop();
        // pivot
        if (x == -1) {
            ans++; q.push(x);
            continue;
        }
        // 발견
        if (x == k) break;
        // 이동
        if (x - 1 >= 0 && !visited[x - 1])
            visited[x - 1] = true, q.push(x - 1);
        if (x + 1 < 100001 && !visited[x + 1])
            visited[x + 1] = true, q.push(x + 1);
        if (x * 2 < 100001 && !visited[2 * x])
            visited[2 * x] = true, q.push(2 * x);
    }
    cout << ans;
    return 0;
}