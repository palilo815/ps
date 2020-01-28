#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

char boong[10][10];
int main()
{
    int row, col; cin >> row >> col;
    loop(i, row) loop(j, col) cin >> boong[i][j];
    loop(i, row) {
        for (int j = col - 1; j >= 0; --j)
            cout << boong[i][j];
        cout << '\n';
    }
    return 0;
}