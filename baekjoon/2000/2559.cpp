#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, K; cin >> N >> K;
    int psum = 0;
    vector<int> vt(K);
    loop(i, K) {
        cin >> vt[i];
        psum += vt[i];
    }

    int ans = psum;
    N -= K;
    loop(i, N) {
        psum -= vt[i % K];
        cin >> vt[i % K];
        psum += vt[i % K];
        ans = max(ans, psum);
    }
    cout << ans;
    return 0;
}