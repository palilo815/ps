#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

char arr[200][20];
int main()
{
    cin.tie(NULL); cout.tie(NULL);
    ios::sync_with_stdio(false);

    int col, row, pos = 0;
    string s;
    cin >> col >> s;
    row = s.size() / col;
    loop(i, row) {
        if (i % 2)
            for (int j = col - 1; j >= 0; --j)
                arr[i][j] = s[pos++];
        else
            loop(j, col)
                arr[i][j] = s[pos++];
    }
    loop(j, col) loop(i, row)
        cout << arr[i][j];
    return 0;
}