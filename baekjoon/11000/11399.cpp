#include <stdio.h>
#include <algorithm>
#define loop(i,n) for(int i=0;i<n;++i)

const int max_N = 1000;
int arr[max_N];
int main()
{
    int N; scanf("%d", &N);
    loop(i, N) scanf("%d", &arr[i]);
    std::sort(arr, arr + N);

    int sum = 0, curr = 0;
    loop(i, N) {
        curr += arr[i];
        sum += curr;
    }
    printf("%d", sum);
    return 0;
}