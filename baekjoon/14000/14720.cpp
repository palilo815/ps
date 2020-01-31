#include <iostream>
using namespace std;

int main()
{
    int N; cin >> N;
    int milk = 0, ans = 0;
    while (N--) {
        int x; cin >> x;
        if (milk == x) {
            ++ans;
            milk = (milk + 1) % 3;
        }
    }
    cout << ans;
    return 0;
}