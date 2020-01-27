#include <stdio.h>
#include <algorithm>
#define loop(i,n) for(int i=0;i<n;++i)

int score[50];
int main()
{
    int T, N;
    scanf("%d", &T);
    loop(t, T) {
        scanf("%d", &N);
        loop(i, N) scanf("%d", &score[i]);
        std::sort(score, score + N);
        int gap = 0;
        loop(i, N - 1) {
            int tmp = score[i + 1] - score[i];
            if (tmp > gap) gap = tmp;
        }
        printf("Class %d\nMax %d, Min %d, Largest gap %d\n", t + 1, score[N - 1], score[0], gap);
    }
    return 0;
}