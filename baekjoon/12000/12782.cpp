#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string a, b;
    int T; cin >> T;
    while(T--){
        cin >> a >> b;
        int len = a.size();
        int _0 = 0, _1 = 0;
        for (int i = 0; i < len; ++i) if (a[i] != b[i]) {
            if (a[i] == '1') ++_1;
            else ++_0;
        }
        cout << _0 + _1 - min(_0, _1) << '\n';
    }
    return 0;
}