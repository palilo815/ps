#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)

const int max_N = 128;

int white, blue;
int colour[max_N][max_N];

bool is_same(int r, int c, int len) {
    int x = colour[r][c];
    loop(i, len) loop(j, len)
        if (colour[r + i][c + j] != x)
            return false;
    return true;
}
void solve(int r, int c, int len) {
    if (is_same(r, c, len)) {
        colour[r][c] ? ++blue : ++white;
        return;
    }
    len /= 2;
    solve(r, c, len);
    solve(r, c + len, len);
    solve(r + len, c, len);
    solve(r + len, c + len, len);
}
int main() {
    int N; scanf("%d", &N);
    loop(i, N) loop(j, N) scanf("%d", &colour[i][j]);
    solve(0, 0, N);
    printf("%d\n%d", white, blue);
    return 0;
}