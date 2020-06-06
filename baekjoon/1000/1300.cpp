#include <cstdio>
typedef long long ll;

int N, K;
int min(int a, int b) {
    return a < b ? a : b;
}
ll solve(int num) {
    ll ret = 0;
    for (int i = 1; i <= N; ++i)
        ret += min(N, num / i);
    return ret;
}
int bs(int l, int r) {
    while (l < r) {
        int m = (l + r) >> 1;
        solve(m) < K ? (l = m + 1) : (r = m);
    }
    return l;
}
int main() {
    scanf("%d %d", &N, &K);
    int l = 0, r = 1e9;
    printf("%d", bs(0, 1e9));
    return 0;
}