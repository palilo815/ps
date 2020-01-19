#include <iostream>
using namespace std;

int main()
{
    int t; cin >> t;
    while (t--) {
        int n, d, ans = 0;
        cin >> n >> d;
        while (n--) {
            int v, f, c;
            cin >> v >> f >> c;
            if (v * f >= c * d) ++ans;
        }
        cout << ans << '\n';
    }
    return 0;
}