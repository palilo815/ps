#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int sudo[9][9];
vector<int> hubo(int r, int c) {
    vector<int> ret;
    bool check[10] = {};
    loop(i, 9) {
        check[sudo[r][i]] = true;
        check[sudo[i][c]] = true;
    }
    int y = (r / 3) * 3, x = (c / 3) * 3;
    loop(i, 3) loop(j, 3)
        check[sudo[y + i][x + j]] = true;
    loop(i, 10)
        if (!check[i])
            ret.push_back(i);
    return ret;
}

// start까지 완료된 board에서 나머지 채우기
// 다 채울 수 있으면 return true
bool solve(int start) {
    for (int i = start + 1;i <= 81;++i) {
        // 9*9칸 전부 채운 경우 성공
        if (i == 81) return true;
        // 0칸 발견
        if (sudo[i / 9][i % 9] == 0) {
            // 해당 칸에 들어갈 수 있는 후보숫자
            vector<int> vt = hubo(i / 9, i % 9);
            // 후보 숫자들로 채워본다.
            for (int x : vt) {
                sudo[i / 9][i % 9] = x;
                if (solve(i)) return true;
            }
            // 만약 위에서 전부 실패한 경우
            // 이 함수를 호출한 쪽에서 숫자를 잘못 넣었다.
            sudo[i / 9][i % 9] = 0;
            return false;
        }
    }
}

int main()
{
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(false);

    loop(i, 9) loop(j, 9)
        cin >> sudo[i][j];
    solve(-1);
    loop(i, 9) {
        loop(j, 9) cout << sudo[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}