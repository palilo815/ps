#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

char** tree;
int row, col;

void DFS(int r, int c) {
    tree[r][c] = 'S';
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= row || C < 0 || C >= col || tree[R][C] != 'T') continue;
        DFS(R, C);
    }
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    while (1) {
        cin >> col >> row;
        if (row == 0) break;

        tree = new char* [row];
        loop(i, row) tree[i] = new char[col];
        
        int r, c;
        loop(i, row) loop(j, col) {
            cin >> tree[i][j];
            if (tree[i][j] == 'S')
                r = i, c = j;
        }

        DFS(r, c);
        loop(i, row) {
            loop(j, col) cout << tree[i][j];
            cout << '\n';
        }

        loop(i, row) delete[] tree[i];
        delete[] tree;
    }
    return 0;
}