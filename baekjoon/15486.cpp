#include <iostream>
#include <algorithm>
#define loop(i,n) for(int i=0;i<n;++i)
#define max_N 1500000
using namespace std;

// time[0], pay[0]은 사용하지 않는다.
int time[max_N + 1], pay[max_N + 1], DP[max_N + 2];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // ** initialize **
    int N; cin >> N;
    for (int i = 1;i <= N;++i)
        cin >> time[i] >> pay[i];

    // basis : DP[0] = 0, 처음 번 돈은 0이다.

    for (int i = 1;i <= N;++i) {
        // 이전값과 비교
        DP[i] = max(DP[i], DP[i - 1]);
        // day : i번 일이 끝난 다음날 (DP[day]부터 새로운 일을 시작할 수 있다.)
        int day = i + time[i];
        if (day <= N + 1)
            DP[day] = max(DP[day], DP[i] + pay[i]);
    }

    // 퇴사 당일날 끝나는 일은 DP[N+1]에 저장되므로 이렇게 출력해야 한다. 
    cout << max(DP[N + 1], DP[N]);
    return 0;
}