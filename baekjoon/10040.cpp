#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int cost[1000], vote[1000];
int main()
{
    int N, M; cin >> N >> M;
    loop(i, N) cin >> cost[i];
    while (M--) {
        int need; cin >> need;
        loop(i,N)
            if (cost[i] <= need) {
                ++vote[i];
                break;
            }
    }
    
    int max_vote = 0, ans;
    loop(i, N)
        if (vote[i] > max_vote) {
            max_vote = vote[i];
            ans = i + 1;
        }
    cout << ans;
    return 0;
}