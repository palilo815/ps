#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

char matA[50][50], matB[50][50];
void rev(int y, int x, int& ans)
{
    ++ans;
    loop(i, 3) loop(j, 3) {
        if (matA[y + i][x + j] == '0') matA[y + i][x + j] = '1';
        else matA[y + i][x + j] = '0';
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int ans = 0, row, col;
    cin >> row >> col;
    loop(i, row) loop(j, col) cin >> matA[i][j];
    loop(i, row) loop(j, col) cin >> matB[i][j];
    
    // 뒤집기 
    loop(i, row - 2) loop(j, col - 2)
        if (matA[i][j] != matB[i][j])
            rev(i, j, ans);

    // 뒤집은 후에도 같지 않다면 -1
    loop(i, row) loop(j, col)
        if (matA[i][j] != matB[i][j]) {
            ans = -1;
            break;
        }
    cout << ans;
    return 0;
}