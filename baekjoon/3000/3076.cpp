#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col, a, b;
    cin >> row >> col >> a >> b;

    loop(i, row) loop(k, a) {
        loop(j, col) {
            char c;
            if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1)) c = 'X';
            else c = '.';
            loop(l, b) cout << c;
        }
        cout << '\n';
    }
    return 0;
}