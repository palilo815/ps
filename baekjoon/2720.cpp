#include<bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int Q = 0, D = 0, N = 0;
        int C; cin >> C;
        Q += C % 25; C /= 25;
        D += C % 10; C /= 10;
        N += C % 5; C /= 5;
        cout << Q << ' ' << D << ' ' << N << ' ' << C << '\n';
    }
    return 0;
}