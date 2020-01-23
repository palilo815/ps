#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int arr[100000];
int b_search(int num, int key, int L, int R)
{
    int ret = INT32_MAX;
    while (L < R) {
        int mid = L + (R - L) / 2;
        if (arr[mid] >= key) {
            ret = min(ret, arr[mid] - num);
            R = mid;
        }
        else L = mid + 1;
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, m, ans = INT32_MAX;
    cin >> n >> m;
    loop(i, n) cin >> arr[i];
    sort(arr, arr + n);
    loop(i, n) {
        int key = arr[i] + m;
        if (arr[i] > 0 && key < 0) break;
        ans = min(ans, b_search(arr[i], key, 0, n));
    }
    cout << ans;
    return 0;
}