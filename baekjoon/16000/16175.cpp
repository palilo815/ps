#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL); cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int N_cand, N_reg;
        cin >> N_cand >> N_reg;

        vector<int> vote(N_cand);
        loop(i, N_reg) loop(j, N_cand) {
            int v; cin >> v;
            vote[j] += v;
        }

        int ans, M = 0;
        loop(i, N_cand)
            if (vote[i] > M) {
                M = vote[i];
                ans = i;
            }
        cout << ans + 1 << '\n';
    }
    return 0;
}