#include <bits/stdc++.h>
using namespace std;

bool broken[10];
int cnt(int n)
{
    // if n을 만들 수 있으면 n의 길이 return (버튼 누르는 횟수)
    // else return 0
    int ret = 0;
    while (n) {
        if (broken[n % 10]) return 0;
        n /= 10;
        ++ret;
    }
    return ret;
}
int main()
{
    int dst, N; cin >> dst >> N;
    while (N--) {
        int x; cin >> x;
        broken[x] = true;
    }

    // 100에서 +/-만 누르는 경우
    int ans = min(abs(dst - 100), abs(100 - dst));
    // 0으로 간 뒤 +만 누르는 경우
    if (!broken[0]) ans = min(ans, 1 + dst);

    for (int i = 1; i < 1000000; ++i) {
        int c = cnt(i);
        if (c) {
            int from_i = min(abs(dst - i), abs(i - dst)) + c;
            if (from_i < ans) ans = from_i;
        }
    }
    cout << ans;
    return 0;
}