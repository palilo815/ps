#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> P;
const int max_N = 100000;

int N, ans, bound;
bool safe[2][100000], visited[2][100000];
void mov(queue<P>& q, int r, int c) {
    if (c >= N) {
        ans = 1;
        return;
    }
    if (c < bound || visited[r][c] || !safe[r][c]) return;
    visited[r][c] = true;
    q.push({ r,c });
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int k;
    cin >> N >> k;
    loop(i, 2) loop(j, N) {
        char c; cin >> c;
        if (c == '1') safe[i][j] = true;
    }
    queue<P> q;
    q.push({ 0,0 }); q.push({ -1,-1 });
    visited[0][0] = true;
    while (ans == 0) {
        int r = q.front().first, c = q.front().second; q.pop();
        if (r == -1) {
            if (q.empty()) break;
            ++bound;
            q.push({ r,c });
            continue;
        }
        if (c < bound) continue;
        mov(q, r, c - 1);
        mov(q, r, c + 1);
        mov(q, 1 - r, c + k);
    }
    cout << ans;
    return 0;
}