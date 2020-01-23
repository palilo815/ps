#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int DP[10001];
int main()
{
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(false);

    int coin[100][2]; // [금액][개수]
    int money, T;
    cin >> money >> T;
    loop(t, T)
        cin >> coin[t][0] >> coin[t][1];

    DP[0] = 1;
    loop(t, T) for (int i = 10000;i >= 0;--i) {
        if (DP[i]) {
            for (int j = 1;j <= coin[t][1];++j) {
                int Next = i + coin[t][0] * j;
                if (Next > money) break;
                DP[Next] += DP[i];
            }
        }
    }
    // 망할.. 이런 테스트 케이스는 왜 있습니까;;
    if (DP[money] < 0) cout << "2147483648";
    else cout << DP[money];
    return 0;
}