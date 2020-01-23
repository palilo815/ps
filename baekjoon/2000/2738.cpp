#include<iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int A[100][100], B[100][100];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col; cin >> row >> col;
    loop(i, row) loop(j, col) cin >> A[i][j];
    loop(i, row) loop(j, col) cin >> B[i][j];
    loop(i, row) {
        loop(j, col) cout << A[i][j] + B[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}