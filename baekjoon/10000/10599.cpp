#include <iostream>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int year[4];
    while (1) {
        loop(i, 4) cin >> year[i];
        loop(i, 4) {
            if (year[i]) break;
            if (i == 3) return 0;
        }
        int min_y = year[2] - year[1], max_y = year[3] - year[0];
        if (min_y < 0) min_y = 0;
        if (max_y < 0) max_y = 0;
        cout << min_y << ' ' << max_y << '\n';
    }
    return 0;
}