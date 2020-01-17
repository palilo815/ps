#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cin.tie(NULL);
    ios::sync_with_stdio(false);

    int a, b, n, arr[5];
    cin >> a >> b;
    n = a * b;
    loop(i, 5) cin >> arr[i];
    loop(i, 5) cout << arr[i] - n << ' ';
    return 0;
}