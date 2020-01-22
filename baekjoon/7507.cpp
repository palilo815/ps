#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define tup tuple<int,int,int>
using namespace std;

tup arr[50000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);
    
    int T, N;
    cin >> T;
    loop(t, T) {
        cin >> N;
        loop(i, N) {
            int d, s, e; cin >> d >> s >> e;
            arr[i] = make_tuple(d, e, s);
        }
        sort(arr, arr + N);

        int ans = 0;
        // 현재 날짜와 시간
        int Day = -1, Time = 0;
        loop(i, N) {
            int d = get<0>(arr[i]), e = get<1>(arr[i]), s = get<2>(arr[i]);

            // 날짜가 변하면 시간도 초기화
            if (d != Day) Day = d, Time = 0;

            // 시작 시간이 이미 지난 경우 무시
            if (s < Time) continue;

            // i번 경기를 본다
            Time = e;
            ++ans;
        }
        cout << "Scenario #" << t + 1 << ":\n";
        cout << ans << "\n\n";
    }
    return 0;
}