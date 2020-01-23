#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int arr[101][101];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int row, col, dy, dx;
        cin >> row >> col >> dy >> dx;

        // 해당 영역을 t번 색종이로 덮어버린다
        loop(i, dy) loop(j, dx)
            arr[row + i][col + j] = t;
    }
    vector<int> ans(T + 1);
    loop(i, 101) loop(j, 101)
        if (arr[i][j])			// 색종이가 붙어있으면
            ++ans[arr[i][j]];	// ans[그 색종이 번호] 1 중가
    for (int i = 1; i <= T; ++i)
        cout << ans[i] << '\n';
    return 0;
}