#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    int T[3][6];
    loop(i, 3) loop(j, 6) cin >> T[i][j];
    loop(i,3) {
        for (int j = 3;j < 6;++j)
            T[i][j] -= T[i][j - 3];
        for (int j = 5;j >= 3;--j)
            if (T[i][j] < 0)
                T[i][j] += 60, --T[i][j - 1];
        for (int j = 3;j < 6;++j)
            cout << T[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}