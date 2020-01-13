#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int arr[101];
// len구간 마다 휴게소가 있도록 배치하는데
// 넣을 수 있는 휴게소는 cnt개다. 가능한가?
// max_N : 구간 끝
bool is_ok(int len, int cnt, int max_N)
{
    int curr = 0;
    loop(i, max_N) {
        while (arr[i] - curr > len) {
            curr += len;
            if (--cnt < 0) return false;
        }
        curr = arr[i];
    }
    return true;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    std::ios::sync_with_stdio(false);

    int N, M, L;
    cin >> N >> M >> L;
    loop(i, N) cin >> arr[i];
    sort(arr, arr + N);
    arr[N] = L;	// 마지막 지점에 휴게소가 있다고 가정하자

    // binary search
    int l = 0, r = 1000, ans = 1000;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (is_ok(mid, M, N + 1)) {
            ans = min(ans, mid);
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    cout << ans;
    return 0;
}