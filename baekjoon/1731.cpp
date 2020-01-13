#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int num[50];
int main()
{
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) cin >> num[i];
    if (num[1] - num[0] == num[2] - num[1])
        cout << num[n - 1] + num[1] - num[0];
    else
        cout << num[n - 1] * (num[1] / num[0]);
    return 0;
}