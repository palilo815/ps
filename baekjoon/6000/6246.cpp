#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

bool balloon[10001];
int main()
{
    cin.tie(NULL), cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N, Q; cin >> N >> Q;
    while (Q--) {
        int start, gap; cin >> start >> gap;
        for (int i = start; i <= N; i += gap)
            balloon[i] = true;
    }
    
    int ans = 0;
    for (int i = 1; i <= N; ++i)
        if (!balloon[i]) ++ans;
    cout << ans;
    return 0;
}