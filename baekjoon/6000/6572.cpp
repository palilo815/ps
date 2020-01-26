#include <iostream>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int r, w, l, P = 0;
    while (cin >> r) {
        if (r == 0) break;
        cin >> w >> l;
        cout << "Pizza " << ++P;
        if (4 * r * r >= w * w + l * l) cout << " fits on the table.\n";
        else cout << " does not fit on the table.\n";
    }
    return 0;
}