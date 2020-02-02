#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, arr[66];
    cin >> N;
    loop(i, N) {
        int Q, P; cin >> Q >> P;
        arr[i] = Q;
    }
    sort(arr, arr + N, greater<int>());
    int x = arr[4], ans = 0;
    for (int i = 5;i < N; ++i) {
        if (arr[i] == x) ++ans;
        else break;
    }
    cout << ans;
    return 0;
}