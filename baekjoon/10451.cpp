#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T, N, arr[1001];
    bool visited[1001];
    cin >> T;
    while (T--) {
        // ** initialize **
        memset(visited, 0, sizeof(visited));
        int ans = 0;
        cin >> N;
        for (int i = 1; i <= N; ++i)
            cin >> arr[i];

        // ** DFS **
        for (int i = 1; i <= N; ++i) {
            if (!visited[i]) {
                ++ans;
                do {
                    visited[i] = true;
                    i = arr[i];
                } while (!visited[i]);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}