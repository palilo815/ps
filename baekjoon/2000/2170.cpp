#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 1000000;

p line[max_N];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> line[i].first >> line[i].second;
    sort(line, line + N);

    int ans = 0;
    int len = 0, l, r = INT_MIN;
    /*
        l, r : 현재 그리고 있는 선의 왼쪽, 오른쪽 끝 위치
        len  : 선의 길이
    */
    loop(i, N) {
        int L = line[i].first, R = line[i].second;
        // 만약 다음에 그릴 선분이 겹치지 않으면,
        // ans에 line을 더해주고 l,r을 모두 갱신
        if (r < L) {
            ans += len;
            l = L, r = R;
        }
        // 겹친다면, 선분의 오른쪽 좌표만 최댓값으로 갱신
        // 왼쪽 좌표는 오름차순이므로 L >= l인 상태다.
        else r = max(r, R);
        len = r - l;
    }
    cout << ans + len;
    return 0;
}