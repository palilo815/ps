#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int cnt[81];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int a, b, c; cin >> a >> b >> c;
    loop(i, a) loop(j, b) loop(k, c)
        ++cnt[i + j + k + 3];

    int tmp = 0, ans = 0;
    loop(i, a + b + c)
        if (cnt[i] > tmp) {
            tmp = cnt[i];
            ans = i;
        }
    cout << ans;
    return 0;
}