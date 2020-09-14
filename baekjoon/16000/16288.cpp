#include <cstdio>

const int mxK = 100;

int q[mxK];

int main() {
    int N, K; scanf("%d%d", &N, &K);
    for (int x, it; N--;) {
        scanf("%d", &x);
        it = -1;
        for (int i = 0; i < K; ++i)
            if (q[i] < x && (it == -1 || q[i] > q[it]))
                it = i;
        if (it == -1) {puts("NO"); return 0;}
        q[it] = x;
    }
    puts("YES");
    return 0;
}