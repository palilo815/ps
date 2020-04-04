#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int MAX = 1000000;

int arr[MAX];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M;
    while (1) {
        cin >> N >> M;
        if (!N && !M) break;
        loop(i, N) cin >> arr[i];
        sort(arr, arr + N);

        int ans = 0;
        while (M--) {
            int x; cin >> x;
            if (binary_search(arr, arr + N, x))
                ++ans;
        }
        cout << ans << '\n';
    }
    return 0;
}