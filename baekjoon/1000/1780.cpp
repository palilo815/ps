#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)

const int max_N = 2187;

int arr[max_N][max_N];
int neg, zero, pos;

bool is_same(int r, int c, int len) {
    int colour = arr[r][c];
    loop(i, len) loop(j, len)
        if (arr[r + i][c + j] != colour) return false;

    if (colour == 1) ++pos;
    else if (colour == -1) ++neg;
    else ++zero;
    return true;
}
void solve(int r, int c, int len) {
    if (is_same(r, c, len)) return;
    len /= 3;
    loop(i, 3) loop(j, 3)
        solve(r + i * len, c + j * len, len);
}
int main() {
    int N; scanf("%d", &N);
    loop(i, N) loop(j, N) scanf("%d", &arr[i][j]);
    solve(0, 0, N);
    printf("%d\n%d\n%d", neg, zero, pos);
    return 0;
}