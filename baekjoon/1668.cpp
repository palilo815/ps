#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int tro[50];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) cin >> tro[i];
    int H = 0, ans1 = 0, ans2 = 0;
    // 왼쪽에서 보는 경우
    loop(i, n)
        if (tro[i] > H)
            H = tro[i], ++ans1;
    H = 0;
    // 오른쪽에서 보는 경우
    for (int i = n - 1; i >= 0;--i)
        if (tro[i] > H)
            H = tro[i], ++ans2;
    cout << ans1 << '\n' << ans2;
    return 0;
}