#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int arr[1000], cache[2][1000], n;
int LIS(int start, int D)
{
    int& ret = cache[D][start];
    if (ret) return ret;
    ret = 1;
    if (D) {
        for (int next = start + 1;next < n;next++)
            if (arr[start] > arr[next])
                ret = max(ret, LIS(next, D) + 1);
    }
    else {
        for (int next = start - 1;next >= 0;next--)
            if (arr[start] > arr[next])
                ret = max(ret, LIS(next, D) + 1);
    }
    return ret;
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> n;
    loop(i, n) cin >> arr[i];
    int ans = 0;
    loop(i, n) {
        int len = LIS(i, 0) + LIS(i, 1) - 1;
        ans = max(ans, len);
    }
    cout << ans;
    return 0;
}