#include <iostream>
using namespace std;

int main()
{
    int n, m, x, y;
    cin >> n >> m;
    bool sam = true, sys = true;
    while (n--) {
        cin >> x >> y;
        if (x != y) sam = false;
    }
    while (m--) {
        cin >> x >> y;
        if (x != y) sys = false;
    }
    if (sam) {
        if (sys) cout << "Accepted";
        else cout << "Why Wrong!!!";
    }
    else cout << "Wrong Answer";
    return 0;
}