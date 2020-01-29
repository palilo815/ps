#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col; cin >> row >> col;

    int x, r, c, R, C;
    bool flag = false;
    loop(i, row) loop(j, col) {
        cin >> x;
        if (x) {
            if (flag) {
                R = i, C = j;
                goto OUT;
            }
            else {
                r = i, c = j;
                flag = true;
            }
        }
    }
OUT:;
    cout << abs(r - R) + abs(c - C);
    return 0;
}