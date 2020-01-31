#include <iostream>
using namespace std;

int main()
{
    int T; cin >> T;
    while (T--) {
        int sum = 0;
        for (int i = 1; i < 17;i++) {
            char c; cin >> c;
            int n = c - '0';
            if (i % 2) n *= 2;
            if (n > 9) n = 1 + (n % 10);
            sum += n;
        }
        if (sum % 10) cout << "F\n";
        else cout << "T\n";
    }
    return 0;
}