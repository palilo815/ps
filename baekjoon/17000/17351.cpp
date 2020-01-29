#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
#define P pair<int,int>
using namespace std;
const int max_N = 500;

// first : 현재 연속된 mola문자의 개수
// second : 포함한 mola의 개수
// ex) m o l a x x m o l은
// mola 한 개를 포함하고, 현재 연속된 "mol"을 가지고 있으므로
// first = 3, second = 1
// mola를 완성할 때마다, first를 0으로 초기화하고 second를 1 늘린다.
P DP[max_N + 1][max_N + 1];
int M[max_N + 1][max_N + 1];

// -1이면 쓸데없는 문자
int conv(char x)
{
    if (x == 'M') return 0;
    if (x == 'O') return 1;
    if (x == 'L') return 2;
    if (x == 'A') return 3;
    return -1;
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    LOOP(i, N) LOOP(j, N) {
        char x; cin >> x;
        M[i][j] = conv(x);
    }

    // 0번 줄을 쓸데없는 문자로 채운다.
    LOOP(i, N) M[i][0] = -1;
    LOOP(i, N) M[0][i] = -1;

    LOOP(i, N) LOOP(j, N) {
        int val = M[i][j];
        P& H = DP[i][j];     // here
        P& U = DP[i - 1][j]; // up
        P& L = DP[i][j - 1]; // left

        // mola 이외의 문자거나, 'm'이면, 주변 칸과 이어져있는지 체크할 필요 없다.
        if (val == -1)
            H.second = max(U.second, L.second);
        else if (val == 0) {
            H.first = 1;
            H.second = max(U.second, L.second);
        }
        // 'o', 'l', 'a'면 주변 칸을 체크해야 한다.
        else {
            // 만약 어느 한 쪽의 mola의 개수가 더 많으면
            // 무조건 그쪽 방향에서 오는게 최적해다.
            if (U.second > L.second) {
                H.second = U.second;
                if (M[i - 1][j] == val - 1 && U.first)
                    H.first = U.first + 1;
            }
            else if (U.second < L.second) {
                H.second = L.second;
                if (M[i][j - 1] == val - 1 && L.first)
                    H.first = L.first + 1;
            }

            // 만약 두 방향의 mola의 개수가 똑같으면
            // 두 방향 모두 조사.
            else {
                H.second = U.second;
                if (M[i - 1][j] == val - 1 && U.first)
                    H.first = U.first + 1;
                else if (M[i][j - 1] == val - 1 && L.first)
                    H.first = L.first + 1;
            }

            // mola를 완성했다면 개수를 1 늘린다.
            if (H.first == 4) {
                H.first = 0;
                ++H.second;
            }
        }
    }

    // DP[i][j].second는, (i,j)에서 완성시킨 mola의 개수
    cout << DP[N][N].second;
    return 0;
}