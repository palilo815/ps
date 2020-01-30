#include<bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int cow[11], ans = 0;
    memset(cow, -1, sizeof(cow));
    int n; cin >> n;
    while (n--) {
        int num, pos; cin >> num >> pos;
        // cow[num] == -1 : num번 소가 처음 발견된 경우
        // cow[num] == pos : 똑같은 자리에서 발견된 경우
        // 이 둘을 제외하곤 ++ans
        if (cow[num] != -1 && cow[num] != pos) ++ans;
        cow[num] = pos;
    }
    cout << ans;
    return 0;
}