#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int a[4];
    while (1) {
        loop(i, 4) cin >> a[i];
        if (a[0] == 0 && a[1] == 0) break;
        loop(i, 4) {
            if (a[i] == 0) {
                if (i == 3) a[i] = a[0] * a[1] * a[2];
                else {
                    int tmp = 1;
                    loop(j, 3) {
                        if (i == j) continue;
                        tmp *= a[j];
                    }
                    a[i] = a[3] / tmp;
                }
            }
            cout << a[i] << ' ';
        }
        cout << '\n';
    }
    return 0;
}