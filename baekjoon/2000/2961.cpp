#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int arr[10][2], N;
int food(int sour, int bit, int id) {
    int ret = abs(sour - bit);
    for (int i = id + 1; i < N; ++i) {
        int S = sour * arr[i][0], B = bit + arr[i][1];
        ret = min(ret, food(S, B, i));
    }
    return ret;
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> N;
    loop(i, N) loop(j, 2) cin >> arr[i][j];
    int ans = INT32_MAX;
    loop(i, N) ans = min(ans, food(arr[i][0], arr[i][1], i));
    cout << ans;
    return 0;
}