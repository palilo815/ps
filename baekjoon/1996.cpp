#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int Map[1000][1000], N;
void Mine(int r, int c, int num)
{
    for (int i = -1;i <= 1;++i) {
        if (r + i < 0 || r + i >= N) continue;
        for (int j = -1;j <= 1;++j) {
            if (c + j < 0 || c + j >= N) continue;
            Map[r + i][c + j] += num;
        }
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> N;
    // 지뢰가 들어오면, 그 숫자만큼 주변칸을 증가시킨다.
    // 그리고 지뢰칸은 -INF를 넣는다.
    // 다른 지뢰칸에서 이 지뢰칸을 증가시켜도 의미 없도록
    loop(i, N) loop(j, N) {
        char x; cin >> x;
        if (x != '.') {
            Mine(i, j, x - '0');
            Map[i][j] = INT32_MIN;
        }
    }

    loop(i, N) {
        loop(j, N) {
            if (Map[i][j] > 9) cout << 'M';
            else if (Map[i][j] < 0) cout << '*';
            else cout << Map[i][j];
        }
        cout << '\n';
    }
    return 0;
}