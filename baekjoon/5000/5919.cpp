#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int h[10000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, avg = 0, ans = 0;
    cin >> n;
    loop(i, n) {
        cin >> h[i];
        avg += h[i];
    }
    avg /= n;
    loop(i, n) ans += abs(h[i] - avg);
    cout << ans / 2;
    return 0;
}