#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

vector<int> invalid[5][3];
/*  고마워요 @jseo
    ###  ..#  ###  ###  #.#  ###  ###  ###  ###  ###
    #.#  ..#  ..#  ..#  #.#  #..  #..  ..#  #.#  #.#
    #.#  ..#  ###  ###  ###  ###  ###  ..#  ###  ###
    #.#  ..#  #..  ..#  ..#  ..#  #.#  ..#  #.#  ..#
    ###  ..#  ###  ###  ..#  ###  ###  ..#  ###  ###
*/
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // (r,c)에 불이 켜졌을 때 불가능한 숫자 목록
    invalid[0][0] = { 1 };
    invalid[0][1] = { 1,4 };
    invalid[0][2] = {};

    invalid[1][0] = { 1,2,3,7 };
    invalid[1][1] = { 0,1,2,3,4,5,6,7,8,9 };
    invalid[1][2] = { 5,6 };

    invalid[2][0] = { 1,7 };
    invalid[2][1] = { 0,1,7 };
    invalid[2][2] = {};

    invalid[3][0] = { 1,3,4,5,7,9 };
    invalid[3][1] = { 0,1,2,3,4,5,6,7,8,9 };
    invalid[3][2] = { 2 };

    invalid[4][0] = { 1,4,7 };
    invalid[4][1] = { 1,4,7 };
    invalid[4][2] = {};

    int N; cin >> N;
    vector<vector<bool>> hubo(N, vector<bool>(10, true));

    // 불이 들어올 때마다, 불가능한 경우를 체크해준다.
    loop(r, 5) loop(c, 4 * N - 1) {
        char x; cin >> x;
        if (x == '#') {
            int idx = c / 4, R = r, C = c % 4;
            for (int num : invalid[R][C])
                hubo[idx][num] = false;
        }
    }

    // total : 만들 수 있는 숫자의 경우의 수
    // ex) 100의 자리 후보 3개, 10의 자리 7개, 1의 자리 5개라면
    //     total = 3 * 7 * 5
    // 만약 중간에, 어느 한 자리라도 만들 수 있는 후보가 없다면 -1이다.
    int total = 1;
    for (auto vt : hubo) {
        int cnt = 0;
        loop(i, 10) if (vt[i]) ++cnt;
        if (cnt == 0) { cout << -1; return 0; }
        total *= cnt;
    }

    // 계산법은 알아 볼 수 있을듯.
    double sum = 0;
    loop(i, N) {
        int sum_digit = 0, cnt = 0;
        loop(j, 10) if (hubo[i][j])
            sum_digit += j, ++cnt;
        double pow10 = pow(10, N - 1 - i);
        sum += pow10 * sum_digit * total / cnt;
    }
    cout << fixed << setprecision(8) << sum / total;
    return 0;
}