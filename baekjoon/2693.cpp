#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t, arr[10];
    cin >> t;
    while (t--) {
        loop(i, 10)
            cin >> arr[i];
        sort(arr, arr + 10);
        cout << arr[7] << '\n';
    }
    return 0;
}