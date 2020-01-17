#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    int arr[6] = { 1,1,2,2,2,8 };
    loop(i, 6) {
        int x;
        scanf("%d", &x);
        arr[i] -= x;
    }
    loop(i, 6)
        printf("%d ", arr[i]);
    return 0;
}