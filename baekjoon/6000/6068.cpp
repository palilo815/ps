#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;

P arr[1000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> arr[i].second >> arr[i].first;
    sort(arr, arr + N, greater<P>());
    // arr.first : 끝내야 하는 시간
    // arr.second : 걸리는 시간

    int ans = INT_MAX;
    loop(i, N) ans = min(ans, arr[i].first) - arr[i].second;
    if (ans < 0) ans = -1;
    cout << ans;
    return 0;
}