#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define loop_in(i,a,b) for(int i=a;i<b;++i)
const int max_k = 12;

int arr[max_k];
int main()
{
    while (1) {
        int k; scanf("%d", &k);
        if (k == 0) break;
        loop(i, k) scanf("%d", &arr[i]);
        loop_in(a, 0, k - 5) loop_in(b, a + 1, k - 4) loop_in(c, b + 1, k - 3) loop_in(d, c + 1, k - 2) loop_in(e, d + 1, k - 1) loop_in(f, e + 1, k)
            printf("%d %d %d %d %d %d\n", arr[a], arr[b], arr[c], arr[d], arr[e], arr[f]);
        putchar('\n');
    }
    return 0;
}