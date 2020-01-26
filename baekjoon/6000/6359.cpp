#include <iostream>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t, n; cin >> t;
    while (t--) {
        cin >> n;
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            // i의 약수의 개수를 구한다.
            int Yak = 0;
            for (int j = 1; j <= i; ++j)
                if (i % j == 0) ++Yak;
            // 약수가 홀수개면 탈출!
            if (Yak % 2 == 1) ++ans;
        }
        cout << ans << '\n';
    }
    return 0;
}