#include <stdio.h>

int main()
{
    int N;
    scanf("%d", &N);
    int inc_max = 0, dec_max = 0;
    int inc = 0, dec = 0;
    int inc_num = 0, dec_num = 100000;
    for (int i = 0; i < N; ++i) {
        int x; scanf("%d", &x);
        if (x >= inc_num) ++inc;
        else {
            if (inc > inc_max) inc_max = inc;
            inc = 1;
        }
        if (x <= dec_num) ++dec;
        else {
            if (dec > dec_max) dec_max = dec;
            dec = 1;
        }
        inc_num = dec_num = x;
    }
    if (inc > inc_max) inc_max = inc;
    if (dec > dec_max) dec_max = dec;
    printf("%d", (inc_max > dec_max ? inc_max : dec_max));
    return 0;
}