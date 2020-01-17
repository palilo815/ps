#include <iostream>
using namespace std;

int main()
{
    int R, B, L, W;
    cin >> R >> B;
    for (W = 1;;++W) {
        if (B % W != 0) continue;
        L = B / W;
        if (R == 2 * (L + W) + 4) break;
    }
    cout << L + 2 << ' ' << W + 2;
    return 0;
}