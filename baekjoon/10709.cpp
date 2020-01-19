#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

char sky[100][100];
int main()
{
    int row, col; cin >> row >> col;
    loop(i, row) loop(j, col) cin >> sky[i][j];
    loop(r, row) {
        int cloud = -1;
        loop(c, col) {
            if (sky[r][c] == 'c')
                cloud = 0;
            cout << cloud << ' ';
            if (cloud != -1) ++cloud;
        }
        cout << '\n';
    }
    return 0;
}