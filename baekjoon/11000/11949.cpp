#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int num[100];
int main()
{
    int n, m; cin >> n >> m;
    loop(i, n) cin >> num[i];
    for (int card = 1; card <= m; ++card)
        loop(i, n - 1)
        if (num[i] % card > num[i + 1] % card)
            swap(num[i], num[i + 1]);
    loop(i, n) cout << num[i] << '\n';
    return 0;
}