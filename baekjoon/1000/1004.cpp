#include <iostream>
using namespace std;

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int x1, y1, x2, y2, N;
        cin >> x1 >> y1 >> x2 >> y2 >> N;
        int ans = 0;
        while (N--) {
            // 중심 (a,b) 반지름 r
            int a, b, r; cin >> a >> b >> r;

            // F1 : 출발지가 원 내부에 들어가는가?
            // F2 : 도착지가 ...
            bool F1 = false, F2 = false;
            if (r * r > (a - x1)* (a - x1) + (b - y1) * (b - y1)) F1 = true;
            if (r * r > (a - x2)* (a - x2) + (b - y2) * (b - y2)) F2 = true;

            // 둘 중 하나만 포함될 경우 무조건 그 원을 통과해야 한다.
            if (F1 ^ F2) ++ans;
        }
        cout << ans << '\n';
    }
    return 0;
}