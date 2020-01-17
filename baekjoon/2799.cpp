#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int Blind[5], tmp[100];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col; cin >> row >> col;
    char c;
    loop(j, 5 * col + 1) cin >> c;
    loop(i, 5 * row) loop(j, 5 * col + 1) {
        cin >> c;
        if (j % 5 == 1 && c == '*')
            ++tmp[(j - 1) / 5];
        if ((i + 1) % 5 == 0 && j == 0) {
            loop(k, col) ++Blind[tmp[k]];
            memset(tmp, 0, sizeof(tmp));
        }
    }
    loop(i, 5)
        cout << Blind[i] << ' ';
    return 0;
}