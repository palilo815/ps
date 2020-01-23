#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cin.tie(NULL);
    ios::sync_with_stdio(false);

    int max_scr = 0, max_idx;
    for (int i = 1; i < 6; i++) {
        int n = 4, sum = 0;
        while (n--) {
            int x; cin >> x;
            sum += x;
        }
        if (sum > max_scr) max_scr = sum, max_idx = i;
    }
    cout << max_idx << ' ' << max_scr;
    return 0;
}