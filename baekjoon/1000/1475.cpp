#include<cstdio>

int cnt[10];
int main() {
    int N; scanf("%d", &N);
    if (!N) {
        putchar('1');
        return 0;
    }

    while (N) {
        ++cnt[N % 10];
        N /= 10;
    }
    cnt[6] = (cnt[6] + cnt[9] + 1) / 2;

    int ans = 0;
    for (int i = 0; i < 9; ++i)
        if (cnt[i] > ans)
            ans = cnt[i];
    printf("%d", ans);
    return 0;
}