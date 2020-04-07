#include <iostream>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    int ans = 0;
    bool east = true;
    for (int i = 0; i < N; ++i) {
        char x; cin >> x;
        if (x == 'E') east = true;
        else {
            if (east) ++ans;
            east = false;
        }
    }
    if (east) ++ans;
    cout << ans;
}