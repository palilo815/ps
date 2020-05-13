#include <iostream>
using namespace std;

const int max_M = 10;

int main() {
    int M; cin >> M;

    int p = (1 << M) - 1;
    int max_p = (1 << max_M) - 1;
    
    while (p <= max_p) {
        for (int i = 0; i < max_M; ++i) {
            cout << (((1 << i) & p) ? '1' : '0') << ' ';
        }
        cout << '\n';

        int t = p | (p - 1);
        p = (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(p) + 1));
    }
    return 0;
}