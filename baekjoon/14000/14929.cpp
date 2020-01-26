#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long
const int max_N = 100000;

int arr[max_N];
int main()
{
    int N, sum = 0;
    ll ans = 0;
    scanf("%d", &N);
    loop(i, N) {
        scanf("%d", &arr[i]);
        sum += arr[i];
    }
    loop(i, N) ans += (ll)arr[i] * (sum - arr[i]);
    printf("%lld", ans / 2);
    return 0;
}