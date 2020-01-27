#include <iostream>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    int M, bus, stop;
    while (1) {
        cin >> s >> M;
        if (s == "#" && M == 0) break;
        cin >> bus >> stop;
        while (stop--) {
            int in, out;
            cin >> out >> in;
            bus += in - out;
            if (bus > M) bus = M;
        }
        cout << s << ' ' << bus << '\n';
    }
    return 0;
}