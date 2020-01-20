#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    int n, arr[500];
    double Sum = 0, Med;
    scanf("%d", &n);
    loop(i, n) {
        scanf("%d", &arr[i]);
        Sum += arr[i];
    }
    sort(arr, arr + n);
    if (n % 2) Med = arr[n / 2];
    else {
        Med = arr[n / 2] + arr[n / 2 - 1];
        Med /= 2.0;
    }
    printf("%.8lf\n", Sum / (double)n);
    printf("%.8lf", Med);
    return 0;
}