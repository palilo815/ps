#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int cnt[7];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    
    int N; cin >> N;
    int ans = 0;
    while (N--) {
        memset(cnt, 0, sizeof(cnt));
        loop(i, 4) {
            int x; cin >> x;
            ++cnt[x];
        }

        int max_cnt = 0, max_eye;
        for (int i = 6; i > 0; --i)
            if (cnt[i] > max_cnt) {
                max_cnt = cnt[i];
                max_eye = i;
            }

        if (max_cnt == 4)
            ans = max(ans, 50000 + max_eye * 5000);
        else if (max_cnt == 3)
            ans = max(ans, 10000 + max_eye * 1000);
        else if (max_cnt == 2) {
            int another = 0;
            for (int i = 1; i < max_eye; ++i)
                if (cnt[i] == 2)
                    another = i;
            if (another)
                ans = max(ans, 2000 + 500 * (max_eye + another));
            else
                ans = max(ans, 1000 + max_eye * 100);
        }
        else
            ans = max(ans, 100 * max_eye);
    }
    cout << ans;
    return 0;
}