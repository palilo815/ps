#include <iostream>
using namespace std;
const int day = 24 * 60 * 60;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int h, m, s, TC; cin >> h >> m >> s >> TC;
    int t = 60 * 60 * h + 60 * m + s;
    int query, x;
    while (TC--) {
        cin >> query;
        if (query == 3) {
            h = t / 3600;
            m = (t % 3600) / 60;
            s = t % 60;
            cout << h << ' ' << m << ' ' << s << '\n';
        }
        else {
            // x < 1000만
            // 1024 * day > 1000만
            cin >> x;
            if (query == 1) t = (t + x) % day;
            else t = (t - x + 1024 * day) % day;
        }
    }
    return 0;
}