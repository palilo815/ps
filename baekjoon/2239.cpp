#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int sudo[9][9];

// (r,c)에 넣을 수 있는 숫자 return
vector<int> hubo(int r, int c) {
    vector<int> ret;
    vector<bool> check(10);
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

// pos칸까지 채운 스도쿠를, 그 이후부터 푼다.
// (5,7) 까지 채웠다면 pos = 5*9+7 = 52
// 만약 끝까지 채운다면 return true
// 도중에 풀 수 없는 경우가 생기면 return false
bool solve(int pos) {
    for (int i = pos + 1;i <= 81;++i) {
        if (i == 81) return true; // 끝까지 다 채운 경우 성공

        // 0인 칸에 가능한 숫자를 넣어보자.
        if (sudo[i / 9][i % 9] == 0) {
            // 현재 칸에 들어갈 수 있는 숫자 vector
            vector<int> vt = hubo(i / 9, i % 9);

            // 가능한 후보를 하나씩 넣어본다.
            // 만약 해당 후보를 넣었을 때 스도쿠가 풀렸다면 return true
            for (int x : vt) {
                sudo[i / 9][i % 9] = x;
                if (solve(i)) return true;
            }

            // 만약 풀리지 않았다면
            // 칸에 다시 0을 넣고 return false
            sudo[i / 9][i % 9] = 0;
            return false;
        }
    }
}

int main()
{
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(false);

    loop(i, 9) loop(j, 9) {
        char c; cin >> c;
        sudo[i][j] = c - '0';
    }
    solve(-1); // (0,0)부터 채우기 시작
    loop(i, 9) {
        loop(j, 9)
            cout << sudo[i][j];
        cout << '\n';
    }
    return 0;
}