#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

bool box[100][100];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T, row, col;
    cin >> T;
    while (T--) {
        cin >> row >> col;
        loop(i, row) loop(j, col) cin >> box[i][j];
        int ans = 0;
        loop(c, col) {
            int bottom = row - 1;
            // 위로 가면서 박스를 발견하면
            // 박스와 바닥까지의 거리를 ans에 합하고
            // 바닥을 한 칸 올린다.
            for (int r = row - 1;r >= 0;--r)
                if (box[r][c])
                    ans += (bottom--) - r;
        }
        cout << ans << '\n';
    }
    return 0;
}