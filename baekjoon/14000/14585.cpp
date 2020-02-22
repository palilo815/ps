#include <bits/stdc++.h>
using namespace std;

bool candy[301][301];
int DP[302][302];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    while (N--) {
        int x, y; cin >> x >> y;
        candy[x][y] = true;
    }
    
    // [i-1][j]와 [i][j-1] 중 최댓값 얻기를 편하게 하기 위해
    // DP[][]에 쓸데없는 한 줄을 추가함.
    for (int i = 1; i < 302; ++i) for (int j = 1; j < 302; ++j) {
        DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
        if (candy[i - 1][j - 1] && M > i + j - 2) DP[i][j] += M - i - j + 2;
    }
    cout << DP[301][301];
    return 0;
}