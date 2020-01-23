#include <iostream>
using namespace std;

int main()
{
    int coin[6] = { 500,100,50,10,5,1 }, ans = 0;
    int x; cin >> x;
    x = 1000 - x;
    for (int i = 0;i < 6;++i) {
        ans += x / coin[i];
        x %= coin[i];
    }
    cout << ans;
    return 0;
}