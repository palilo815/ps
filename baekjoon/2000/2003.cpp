#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int arr[10000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    loop(i, N) cin >> arr[i];

    int l = 0, r = -1, psum = 0, ans = 0;
    // psum = [l,r]구간의 합
    while (1) {
        if (psum < M) {
            if (++r == N) break;
            psum += arr[r];
        }
        else if (psum > M)
            psum -= arr[l++];
        else {
            ++ans;
            psum -= arr[l++];
        }
    }
    cout << ans;
    return 0;
}