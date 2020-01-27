#include <iostream>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int a, b, t = 0;
    string op, res[2] = {"false\n", "true\n"};
    while (1) {
        cin >> a >> op >> b;
        if (op == "E") break;
        bool f;
        if (op == ">") f = (a > b);
        else if (op == ">=") f = (a >= b);
        else if (op == "<") f = (a < b);
        else if (op == "<=") f = (a <= b);
        else if (op == "==") f = (a == b);
        else f = (a != b);
        cout << "Case " << ++t << ": " << res[f];
    }
    return 0;
}