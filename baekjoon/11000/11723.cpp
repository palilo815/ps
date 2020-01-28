#include <iostream>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string op;
    int S = 0, m, x;
    cin >> m;
    while (m--) {
        cin >> op;
        if (op == "all") S = (1 << 21) - 1;
        else if (op == "empty") S = 0;
        else {
            cin >> x;
            if (op == "add") S |= (1 << x);
            else if (op == "remove") S &= ~(1 << x);
            else if (op == "toggle") S ^= (1 << x);
            else {
                if (S & (1 << x)) cout << "1\n";
                else cout << "0\n";
            }
        }
    }
    return 0;
}