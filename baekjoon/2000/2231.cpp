#include <cstdio>

int cnt(int n) {
    int ret = 0;
    while (n) {
        ++ret;
        n /= 10;
    }
    return ret;
}
int sum(int n) {
    int ret = n;
    while (n) {
        ret += n % 10;
        n /= 10;
    }
    return ret;
}
int main() {
    int N; scanf("%d", &N);
    int ans = 0;
    for (int i = N - 9 * cnt(N); i <= N; ++i)
        if (N == sum(i)) {
            ans = i;
            break;
        }
    printf("%d", ans);
    return 0;
}