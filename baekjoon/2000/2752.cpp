#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    int arr[3];
    loop(i, 3) cin >> arr[i];
    sort(arr, arr + 3);
    loop(i, 3) cout << arr[i] << ' ';
    return 0;
}