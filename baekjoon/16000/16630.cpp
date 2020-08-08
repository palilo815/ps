#include <iostream>
using namespace std;

const int mx = 2e5;

char s[mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N >> s;
    s[N - 1] = 'R';
    int k = -1;
    for (int i = 0; i < N; ++i)
        if (s[i] == 'R') {
            for (int j = i; j ^ k; --j)
                cout << j + 1 << '\n';
            k = i;
        }
    return 0;
}