#include <stdio.h>
#include <algorithm>
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long
const int max_N = 1000000;
#define scanf scanf_s

ll arr[max_N];
ll rev(ll n)
{
    ll ret = 0;
    while (n) {
        ret *= 10;
        ret += n % 10;
        n /= 10;
    }
    return ret;
}
int main()
{
    int n;
    scanf("%d", &n);
    ll num;
    loop(i, n) {
        scanf("%lld", &num);
        arr[i] = rev(num);
    }
    std::sort(arr, arr + n);
    loop(i, n)
        printf("%lld\n", arr[i]);
    return 0;
}