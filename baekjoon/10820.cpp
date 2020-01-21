#include <iostream>
#include <string>
using namespace std;
int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    string w;
    while (getline(cin, w)) {
        int s = 0, b = 0, n = 0, x = 0;
        for (int i = 0; i < w.size(); ++i) {
            if (w[i] < '0') x++;
            else if (w[i] < 'A') n++;
            else if (w[i] < 'a') b++;
            else s++;
        }
        cout << s << ' ' << b << ' ' << n << ' ' << x << '\n';
    }
    return 0;
}