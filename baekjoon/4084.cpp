#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool cvg(int* arr)
{
    for (int i = 1; i < 4; ++i)
        if (arr[i] != arr[0])
            return false;
    return true;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int a[4], tmp[4];
    while (1) {
        loop(i, 4) cin >> a[i];
        if (a[0] == 0) break;
        int ans = 0;
        while (!cvg(a)) {
            int tmp[4];
            loop(i, 4) tmp[i] = abs(a[i] - a[(i + 1) % 4]);
            loop(i, 4) a[i] = tmp[i];
            ++ans;
        }
        cout << ans << '\n';
    }
    return 0;
}