#include <iostream>
using namespace std;

int main()
{
    int N; cin >> N;
    int ans = 0;
    bool press_A = false;
    while (N--) {
        double d; cin >> d;
        int i = d;
        if (!press_A && d - i > 0.1) {
            ++ans;
            press_A = true;
        }
        ans += i;
        if (i > 0) press_A = true;
    }
    cout << ans;
    return 0;
}