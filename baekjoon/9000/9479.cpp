#include <iostream>
using namespace std;
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string ping;
    while (1) {
        cin >> ping;
        if (ping == "0") break;
        int len = ping.size();
        for (int i = 1; i < len; ++i) if (ping[i] == '1') {
            cout << i << ' ';
            for (int j = i * 2; j < len; j += i)
                ping[j] = (ping[j] == '1' ? '0' : '1');
        }
        cout << '\n';
    }
    return 0;
}