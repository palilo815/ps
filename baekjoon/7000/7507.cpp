#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef tuple<int, int, int> tup;

tup arr[50000];
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    loop(t, T) {
        int N; cin >> N;
        loop(i, N) {
            int d, s, e; cin >> d >> s >> e;
            arr[i] = { d,e,s };
        }
        sort(arr, arr + N);

        int ans = 0;
        // 현재 날짜와 시간
        int _day = -1, _time = 0;
        loop(i, N) {
            auto [d, e, s] = arr[i];

            // 날짜가 변하면 시간도 초기화
            if (d != _day) _day = d, _time = 0;

            // 시작 시간이 이미 지난 경우 무시
            if (s < _time) continue;

            // i번 경기를 본다
            _time = e;
            ++ans;
        }
        cout << "Scenario #" << t + 1 << ":\n";
        cout << ans << "\n\n";
    }
    return 0;
}