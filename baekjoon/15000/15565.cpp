#include<bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    vector<int> gap;
    int N, K; cin >> N >> K;

    int apeach = 0;
    while (N--) {
        int x; cin >> x;
        if (x == 1) {
            gap.push_back(apeach);
            apeach = 0;
        }
        else ++apeach;
    }
    // vector에는 라이언 인형 개수만큼의 숫자가 들어있고,
    // 그 숫자는 왼쪽에 놓은 어피치의 개수이다.
    // ex) 어 라 라 어 어 어 라 어 어 어 어
    // gap = {1,0,3}
    // 우리는 왼쪽 끝의 어피치 1개, 오른쪽 끝의 어피치4개는 절대 답에 포함되지 않는다.
    // 따라서 vector에 오른쪽 끝 4개는 아예 넣지 않으며, index 0도 고려하지 않는다.

    int len = gap.size();
    if (len < K) { cout << -1; return 0; }

    // gap vector에서 연속된 K - 1개의 값이 의미하는 것은
    // K개의 라이언 사이에 있는 어피치의 개수이다. 
    // 따라서 K + sum( gap[a,a+K) ) == a부터 K개의 라이언 인형을 골랐을 때, 그 길이
    
    // 일단 ans에 맨 처음부터 K개를 골랐을 때의 길이를 넣는다.
    int psum = K;
    for (int i = 1; i < K; ++i)
        psum += gap[i];
    int ans = psum;

    // 오른쪽 라이언을 추가하고, 맨 왼쪽 라이언을 빼는 방식으로 반복한다.
    for (int i = 1; i <= len - K; ++i) {
        psum += gap[i + K - 1] - gap[i];
        ans = min(ans, psum);
    }
    cout << ans;
    return 0;
}