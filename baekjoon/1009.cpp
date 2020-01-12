#include <iostream>
using namespace std;

int main() {
    cin.tie(NULL), cout.tie(NULL);
    std::ios::sync_with_stdio(false);

    int t, a, b;
    int arr[4];
    cin >> t;
    while (t--) {
        cin >> a >> b;
        arr[0] = a % 10;
        for (int i = 1; i < 4; i++)
            arr[i] = (arr[i - 1] * arr[0]) % 10;
        int ans = arr[(b - 1) % 4];
        if (ans == 0)
            cout << "10\n";
        else
            cout << ans << '\n';
    }
    return 0;
}