#include <iostream>
#include <cstring>
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long
using namespace std;

ll DP[2][21]; // 소중한 메모리 아껴쓰쟈
int main()
{
    int N, num; cin >> N >> num;

    // basis
    // 첫 번째 숫자의 부호는 무조건 +이므로, 따로 처리해주어야 한다.
    DP[0][num] = 1;

    loop(i, N - 2) {
        int idx = i % 2;
        cin >> num;
        memset(DP[1 - idx], 0, sizeof(DP[1 - idx]));

        // j를 만들 수 있으면 j+num, j-num도 만들 수 있다.
        loop(j, 21)
            if (DP[idx][j]) {
                if (j + num <= 20) DP[1 - idx][j + num] += DP[idx][j];
                if (j - num >= 0) DP[1 - idx][j - num] += DP[idx][j];
            }
    }
    cin >> num;
    cout << DP[N % 2][num];
    return 0;
}