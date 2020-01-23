#include <iostream>
using namespace std;

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int A = 0, B = 0;
        int n; cin >> n;
        while (n--) {
            char a, b; cin >> a >> b;
            if (a == b) continue;
            if ((a == 'P' && b == 'R') || (a == 'R' && b == 'S') || (a == 'S' && b == 'P')) ++A;
            else ++B;
        }
        if (A == B) cout << "TIE\n";
        else {
            cout << "Player ";
            if (A > B) cout << "1\n";
            else cout << "2\n";
        }
    }
    return 0;
}