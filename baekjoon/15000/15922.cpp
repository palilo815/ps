#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int ans = 0, line = 0;
    int L_prev, R_prev = INT_MIN;
    
    int N; cin >> N;
    while (N--) {
        int L_curr, R_curr; cin >> L_curr >> R_curr;
        
        // 새로 그리는 선이 이전에 그린 선과 겹치지 않는 경우
        // 이전의 선 길이(line)을 정답에 추가.
        if (L_curr > R_prev) {
            ans += line;
            L_prev = L_curr, R_prev = R_curr;
        }

        // 겹치는 경우
        else {
            L_prev = min(L_prev, L_curr);
            R_prev = max(R_prev, R_curr);
        }
        line = R_prev - L_prev;
    }
    cout << ans + line;
    return 0;
}