#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;
const int max_N = 500000;

int arr[500000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    int sum_stick = 0;
    loop(i, N) {
        cin >> arr[i];
        sum_stick += arr[i];
    }
    sort(arr, arr + N);

    // 가장 작은 조각부터 낱개로 잘라낸다.
    ll ans = 0;
    loop(i, N - 1) {
        sum_stick -= arr[i];
        ans += ll(sum_stick) * arr[i];
    }
    cout << ans;
    return 0;
}