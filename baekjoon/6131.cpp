#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, ans = 0;
    cin >> n;
    for (int a = 1; a <= 500; ++a)
        for (int b = a + 1; b <= 500; ++b) {
            if (a * a + n == b * b) ++ans;
            else if (a * a + n < b * b) break;
        }
    cout << ans;
    return 0;
}