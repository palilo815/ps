#include<iostream>
#include<algorithm>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int num[200], cache[200];
int LIS(int start, int end)
{
    int& ret = cache[start];
    if (ret) return ret;
    ret = 1;
    for (int next = start + 1;next < end; next++)
        if (num[start] < num[next])
            ret = max(ret, LIS(next, end) + 1);
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) cin >> num[i];

    int lis = 0;
    loop(i, n)
        lis = max(lis, LIS(i, n));
    cout << n - lis;
    return 0;
}