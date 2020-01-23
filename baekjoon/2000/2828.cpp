#include<iostream>
using namespace std;

int main()
{
    int n, s = 1, e, j, ans = 0;
    cin >> n >> e >> j;
    while (j--) {
        int x; cin >> x;
        if (x > e) {
            int gap = x - e;
            s += gap, e += gap, ans += gap;
        }
        else if (x < s) {
            int gap = s - x;
            s -= gap, e -= gap, ans += gap;
        }
    }
    cout << ans;
    return 0;
}