#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int mov[4][2] = { 1,0,0,1,-1,0,0,-1 }; // 북 동 남 서
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        string s; cin >> s;
        int len = s.size();
        int y = 0, x = 0, y_min = 0, x_min = 0, y_max = 0, x_max = 0, D = 0;
        loop(i, len) {
            if (s[i] == 'R') D = (D + 1) % 4;
            else if (s[i] == 'L') D = (D + 3) % 4;
            else {
                if (s[i] == 'F') y = y + mov[D][0], x = x + mov[D][1];
                else y = y - mov[D][0], x = x - mov[D][1];

                y_min = min(y_min, y), y_max = max(y_max, y);
                x_min = min(x_min, x), x_max = max(x_max, x);
            }
        }
        cout << (y_max - y_min) * (x_max - x_min) << '\n';
    }
    return 0;
}