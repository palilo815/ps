#include <iostream>
#include <algorithm>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

bool hidden[1001][1001];
int dots[1001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // 2d Eratosthenes
    hidden[0][0] = true;
    loop(y, 1001) loop(x, 1001)
        if (!hidden[y][x]) {
            for (int n = max(y, x);n < 1001;++n)
                ++dots[n];
            for (int Y = 2 * y, X = 2 * x;Y < 1001 && X < 1001;Y += y, X += x)
                hidden[Y][X] = true;
        }
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        cout << dots[n] << '\n';
    }
}