#include <iostream>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int x, prev_x = -1000000;
    bool flag = true;
    while (cin >> x) {
        if (x < prev_x) {
            flag = false;
            break;
        }
        prev_x = x;
    }
    if (flag) cout << "Good";
    else cout << "Bad";
    return 0;
}