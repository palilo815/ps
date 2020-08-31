#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int arr[10001];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    while (cin >> n >> m) {
        if (n == 0) break;
        memset(arr, 0, sizeof(arr));

        while (n--)
            loop(i, m) {
            int x; cin >> x;
            ++arr[x];
        }

        int Yim = 0, Hong = 0;
        loop(i, 10001) {
            if (arr[i] > Yim)
                Hong = Yim, Yim = arr[i];
            else if (arr[i] > Hong)
                Hong = arr[i];
        }

        loop(i, 10001) if (arr[i] == Hong)
            cout << i << ' ';
        cout << '\n';
    }
    return 0;
}