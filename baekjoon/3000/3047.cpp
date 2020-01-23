#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int arr[3];
    char order[3];
    loop(i, 3) cin >> arr[i];
    loop(i, 3) cin >> order[i];
    sort(arr, arr + 3);
    loop(i, 3) cout << arr[order[i] - 'A'] << ' ';
    return 0;
}