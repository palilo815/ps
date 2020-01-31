#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 1000;

int psum_A[max_N + 1], psum_B[max_N + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    int len_A, len_B;
    cin >> len_A;
    loop(i, len_A) {
        int x; cin >> x;
        psum_A[i + 1] = psum_A[i] + x;
    }
    cin >> len_B;
    loop(i, len_B) {
        int x; cin >> x;
        psum_B[i + 1] = psum_B[i] + x;
    }
    
    // vt에 모든 A의 부분배열의 합을 저장
    vector<int> vt;
    loop(i, len_A)
        for (int j = i + 1; j <= len_A; ++j)
            vt.push_back(psum_A[j] - psum_A[i]);
    sort(vt.begin(), vt.end());

    // ans는 int범위를 넘을 수 있다.
    long long ans = 0;
    loop(i,len_B)
        for (int j = i + 1; j <= len_B; ++j) {
            int key = T - (psum_B[j] - psum_B[i]);
            // 값이 key인 부분배열이 하나가 아닐 수 있으므로 범위를 더해준다.
            auto low = lower_bound(vt.begin(), vt.end(), key);
            if (*low == key)
                ans += upper_bound(vt.begin(), vt.end(), key) - low;
        }
    cout << ans;
    return 0;
}