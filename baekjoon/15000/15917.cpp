#include <iostream>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int Q, n;
    cin >> Q;
    while (Q--) {
        cin >> n;
        cout << ((n & (-n)) == n) << '\n';
    }
    return 0;
}