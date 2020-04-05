#include <cstdio>
typedef long long ll;

const int MAX = 100;

ll DP[MAX + 1][MAX + 1];
int broken[MAX + 1][MAX + 1];

inline void swap(int& a, int& b) {
    int tmp = a; a = b; b = tmp;
}
int main() {
    int col, row, K;
    scanf("%d %d %d", &col, &row, &K);
    while (K--) {
        int ux, uy, vx, vy;
        scanf("%d %d %d %d", &ux, &uy, &vx, &vy);
        if (ux + uy > vx + vy)
            swap(ux, vx), swap(uy, vy);
        broken[ux][uy] |= (ux + 1 == vx ? 1 : 2);
    }
    
    // ** 좆같은 문제 공사중인 도로가 중복으로 들어옴 ㅅㅂ **
    // broken & 1 : x축으로 못 감
    // broken & 2 : y축으로 못 감

    DP[0][0] = 1;
    for (int x = 0; x <= col; ++x) for (int y = 0; y <= row; ++y) {
        if (!(broken[x][y] & 1) && x < col)
            DP[x + 1][y] += DP[x][y];
        if (!(broken[x][y] & 2) && y < row)
            DP[x][y + 1] += DP[x][y];
    }
    printf("%lld", DP[col][row]);
    return 0;
}