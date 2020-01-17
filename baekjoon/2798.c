#include <stdio.h>
#include <stdlib.h>
#define loop(i,n) for(int i=0;i<n;++i)

int card[100];
int main()
{
    int N, val;
    scanf("%d %d", &N, &val);
    loop(i, N) scanf("%d", &card[i]);
    int max = 0;
    loop(i, N) {
        int sum = card[i];
        if (sum > val) continue;
        for (int j = i + 1; j < N; j++) {
            if (sum + card[j] > val) continue;
            else
                sum += card[j];
            for (int k = j + 1; k < N; k++) {
                if (sum + card[k] > val) continue;

                else {
                    sum += card[k];
                    if (sum > max) max = sum;
                    sum -= card[k];
                }
            }
            sum -= card[j];
        }
    }
    printf("%d", max);
    return 0;
}