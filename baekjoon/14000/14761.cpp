#include <iostream>
using namespace std;

int main()
{
    int X, Y, N;
    cin >> X >> Y >> N;
    for (int i = 1; i <= N; ++i) {
        bool flag = true;
        if (i % X == 0) {
            cout << "Fizz";
            flag = false;
        }
        if (i % Y == 0) {
            cout << "Buzz";
            flag = false;
        }
        if (flag) cout << i;
        cout << '\n';
    }
    return 0;
}