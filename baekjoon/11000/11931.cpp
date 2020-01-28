#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 1000000;

int arr[max_N];
int main()
{
    int N; scanf("%d", &N);
    loop(i, N) scanf("%d", &arr[i]);
    sort(arr, arr + N, greater<int>());
    loop(i, N) printf("%d\n", arr[i]);
    return 0;
}