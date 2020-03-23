#include <iostream>
using namespace std;

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string A, B;
    int T, N;
    cin >> T;
    while (T--) {
        cin >> A >> N;
        int len = A.size(), _min = 129;
        string ans = "~";
        while (N--) {
            int cnt = 0;
            cin >> B;
            for (int i = 0; i < len; ++i)
                if (A[i] != B[i]) ++cnt;
            if (cnt < _min) {
                _min = cnt;
                ans = B;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}