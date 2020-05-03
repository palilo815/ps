#include <iostream>
using namespace std;

int passed[100001];
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int G, P; cin >> G >> P;
    int ans = 0;
    while (P--) {
        int gate; cin >> gate;
        while (gate > 0 && passed[gate] > 0) {
            int mov = passed[gate]++;
            gate -= mov;
        }

        if (gate <= 0) break;

        ++ans;
        passed[gate] = 1;
    }
    cout << ans;
    return 0;
}