#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int cache[100001];
int max_Hail(int n)
{
    if (n == 1) return 1;
    if (n > 100000) {
        if (n % 2) return max(n, max_Hail(3 * n + 1));
        else return max(n, max_Hail(n / 2));
    }
    int& ret = cache[n];
    if (ret) return ret;
    if (n % 2)
        return ret = max(n, max_Hail(3 * n + 1));
    else
        return ret = max(n, max_Hail(n / 2));
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        cout << max_Hail(n) << '\n';
    }
    return 0;
}