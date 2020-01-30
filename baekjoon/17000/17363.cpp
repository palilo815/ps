#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

char milk[100][100];
char conv(char c)
{
    switch (c) {
    case('.'): return '.';
    case('O'): return 'O';
    case('-'): return '|';
    case('|'): return '-';
    case('/'): return '\\';
    case('\\'): return '/';
    case('^'): return '<';
    case('<'): return 'v';
    case('v'): return '>';
    case('>'): return '^';
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col; cin >> row >> col;
    loop(i, row) loop(j, col) cin >> milk[i][j];
    loop(i, col) {
        loop(j, row) cout << conv(milk[j][col - 1 - i]);
        cout << '\n';
    }
    return 0;
}