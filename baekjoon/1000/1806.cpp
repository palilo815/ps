#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int arr[100000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    std::ios::sync_with_stdio(false);

    int N, S; cin >> N >> S;
    loop(i, N) cin >> arr[i];

    int ans = INT32_MAX, psum = 0;
    // two-pointer
    int i = 0, j = -1;	// [i, j]
    while (j < N) {
        if (psum < S)
            psum += arr[++j];
        else {
            ans = min(ans, j - i + 1);
            psum -= arr[i++];
        }
    }
    if (ans == INT32_MAX) ans = 0;
    cout << ans;
    return 0;
}