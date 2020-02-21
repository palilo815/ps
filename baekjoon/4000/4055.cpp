#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define scanf scanf_s

const int max_N = 100;

int s[max_N], e[max_N];

int greedy(int t, int N) {
    int ret = -1, earliest = 49;
    loop(i, N)
        if (s[i] <= t && t < e[i] && e[i] < earliest) {
            ret = i;
            earliest = e[i];
        }
    return ret;
}
int main() {
    int day = 0;
    while (1) {
        int N; scanf("%d", &N);
        if (N == 0) break;
        loop(i, N) scanf("%d %d", &s[i], &e[i]);
        loop(i, N) s[i] *= 2, e[i] *= 2;

        int ans = 0;
        for (int t = 16; t < 48; ++t) {
            int idx = greedy(t, N);
            if (idx >= 0) {
                ++ans;
                s[idx] = 48;
            }
        }
        printf("On day %d Emma can attend as many as %d parties.\n", ++day, ans);
    }
    return 0;
}