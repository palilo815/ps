#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool visited[1000001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int f, s, g, u, d, ans = 0;
    cin >> f >> s >> g >> u >> d;

    queue<int> q;
    q.push(s);
    q.push(-1); // pivot
    while (1) {
        int here = q.front(); q.pop();

        // 정답 찾으면 종료
        if (here == g) break;

        // pivot일시
        // queue에 pivot만 있다 : 탐색 불가
        // 아니면 ++ans하고 계속 진행
        if (here == -1) {
            if (q.empty()) break;
            ans++;
            q.push(here);
            continue;
        }
        int U = here + u, D = here - d;
        if (U <= f && !visited[U]) q.push(U), visited[U] = true;
        if (D > 0 && !visited[D]) q.push(D), visited[D] = true;
    }

    if (!q.empty()) cout << ans;
    else cout << "use the stairs";
    return 0;
}