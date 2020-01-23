#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, A, B; cin >> N >> A >> B;
    vector<int> T1(A), T2(B);
    loop(i, A) cin >> T1[i];
    loop(i, B) cin >> T2[i];
    sort(T1.begin(), T1.end());
    sort(T2.begin(), T2.end());

    // N이 홀수일 경우 가장 예쁜 2x1타일을 하나 사용
    int ans = 0;
    if (N % 2) {
        ans += T1.back();
        T1.pop_back();
        --N;
    }
    // N은 이제 무조건 짝수

    // 2x1타일 두 개 vs 2x2타일 한 개를 비교해서 더 예쁜 방법으로 채운다.
    while (N) {
        // 만약 여분의 타일이 없으면 해당 beauty값은 0에서 변화 없음
        int beauty1 = 0, beauty2 = 0;
        int s1 = T1.size(), s2 = T2.size();
        if (s1 > 1)
            beauty1 = T1[s1 - 1] + T1[s1 - 2];
        if (s2 > 0)
            beauty2 = T2[s2 - 1];

        if (beauty1 > beauty2) {
            ans += beauty1;
            T1.pop_back(), T1.pop_back();
        }
        else {
            ans += beauty2;
            T2.pop_back();
        }
        N -= 2;
    }
    cout << ans;
    return 0;
}