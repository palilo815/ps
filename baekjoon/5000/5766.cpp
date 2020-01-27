#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

// 랭킹에 오른 횟수
int arr[10001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, m;
    while (cin >> n >> m) {
        if (n == 0) break;
        memset(arr, 0, sizeof(arr));
        while (n--)
            loop(i, m) {
                int x; cin >> x;
                ++arr[x];
            }

        // 임요환, 홍진호
        int Yim = 0, Hong = 0;
        loop(i, 10001) {
            if (arr[i] > Yim)
                Hong = Yim, Yim = arr[i];
            else if (arr[i] > Hong)
                Hong = arr[i];
        }
        loop(i, 10001)
            if (arr[i] == Hong) cout << i << ' ';
        cout << '\n';
    }
    return 0;
}