#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long
using namespace std;

const int max_N = 1000000;
ll arr[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> arr[i];
    sort(arr, arr + N);
    ll prev_num = arr[0], ans = arr[0];
    int cnt = 1, max_cnt = 1;
    for (int i = 1;i < N;++i) {
        if (arr[i] == prev_num) ++cnt;
        else {
            if (max_cnt < cnt) {
                max_cnt = cnt;
                ans = prev_num;
            }
            prev_num = arr[i];
            cnt = 1;
        }
    }
    if (max_cnt < cnt) {
        max_cnt = cnt;
        ans = prev_num;
    }
    cout << ans;
    return 0;
}