#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int board[1000];
int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int n, m; cin >> n >> m;
    loop(i, n) cin >> board[i];

    int pos = 0, ans = 0;
    while (1) {
        // 1번 주사위 굴린다.
        ++ans;
        int mov; cin >> mov;

        // 눈만큼 이동
        pos += mov;
        if (pos >= n - 1) break;

        // 도착지의 명령대로 이동
        pos += board[pos];
        if (pos >= n - 1) break;
    }
    cout << ans;
    return 0;
}