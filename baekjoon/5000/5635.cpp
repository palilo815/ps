#include <iostream>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, old = 100000000, young = 0;
    string O, Y, name;
    cin >> n;
    while (n--) {
        int d, m, y;
        cin >> name >> d >> m >> y;
        int age = 10000 * y + 100 * m + d;
        if (age < old) {
            old = age;
            O = name;
        }
        if (age > young) {
            young = age;
            Y = name;
        }
    }
    cout << Y << '\n' << O;
    return 0;
}