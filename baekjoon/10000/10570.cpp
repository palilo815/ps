#include <iostream>
#include <cstring>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int cnt[1001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t, n, x;
    cin >> t;
    while (t--) {
        memset(cnt, 0, sizeof(cnt));
        cin >> n;
        while (n--) {
            cin >> x;
            ++cnt[x];
        }
        int max_cnt = 0, ans;
        loop(i, 1001)
            if (cnt[i] > max_cnt) {
                max_cnt = cnt[i];
                ans = i;
            }
        cout << ans << '\n';
    }
    return 0;
}