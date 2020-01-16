#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int n, arr[20000];
int Sum(int index)
{
    int ret = 0;
    for (int i = 0; i < index; ++i)
        ret += arr[index] - arr[i];
    for (int i = index + 1; i < n; ++i)
        ret += arr[i] - arr[index];
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> n;
    loop(i, n) cin >> arr[i];
    sort(arr, arr + n);
    int mid = n / 2;
    int Ans = arr[mid], MIN = Sum(mid);
    for (int i = mid - 1; i >= 0; --i) {
        int gap = Sum(i);
        if (gap <= MIN) {
            Ans = arr[i];
            MIN = gap;
        }
        else break;
    }
    for (int i = mid + 1; i < n; ++i) {
        int gap = Sum(i);
        if (gap < MIN) {
            Ans = arr[i];
            MIN = gap;
        }
        else break;
    }
    cout << Ans;
    return 0;
}