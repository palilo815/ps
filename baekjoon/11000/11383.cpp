#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

char Before[10][10], After[10][20];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col; cin >> row >> col;
    bool f = true;
    loop(i, row) loop(j, col) cin >> Before[i][j];
    loop(i, row) loop(j, 2 * col) cin >> After[i][j];
    loop(i, row) {
        for (int j = 0; j < col; ++j) {
            char c = Before[i][j];
            if (After[i][2 * j] != c) { f = false; goto OUT; }
            if (After[i][2 * j + 1] != c) { f = false; goto OUT; }
        }
    }
OUT:;
    if (f) cout << "Eyfa";
    else cout << "Not Eyfa";
    return 0;
}