#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 4;

int price[max_N * 2];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T, N, p;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cin >> N;
        loop(i, 2 * N) cin >> price[i];
        cout << "Case #" << t << ':';

        // 할인가에 해당하는 정가를 -1로 바꾼다.
        int i = 0;
        while (N--) {
            // 지워진 숫자 전부 pass
            while (price[i] < 0) ++i;

            // 할인가를 출력하고, 그에 맞는 정가를 normal price에 저장
            cout << ' ' << price[i];
            int normal_p = price[i] / 3 * 4;

            // 정가 index를 찾아서 -1로 바꾼다.
            int j = ++i;
            while (price[j] != normal_p) ++j;
            price[j] = -1;
        }
        cout << '\n';
    }
    return 0;
}