#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

// 이곳에 돌의 위치를 기록한다.
bool board[8][8];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s; int n, r, c;
    cin >> s;
    c = s[0] - 'A', r = s[1] - '1';
    cin >> s;
    board[s[1] - '1'][s[0] - 'A'] = true;

    cin >> n;
    while (n--) {
        int R = r, C = c;
        cin >> s;
        loop(i, s.size()) {
            char D = s[i];
            if (D == 'R') ++C;
            else if (D == 'L') --C;
            else if (D == 'T') ++R;
            else --R;
        }
        // (R,C) : 이동 후 좌표
        if (R == -1 || R == 8 || C == -1 || C == 8) continue;

        //만약 이동한 좌표에 돌이 있으면
        // 같은 방향으로 옮긴다. (rr,cc) : 돌의 이동 후 좌표
        if (board[R][C]) {
            int rr = R + (R - r), cc = C + (C - c);
            if (rr == -1 || rr == 8 || cc == -1 || cc == 8) continue;
            board[R][C] = false;
            board[rr][cc] = true;
        }
        r = R, c = C;
    }
    cout << (char)(c + 'A') << (char)(r + '1') << '\n';
    loop(i, 8) loop(j, 8)
        if (board[i][j]) {
            cout << (char)(j + 'A') << (char)(i + '1');
            break;
        }
    return 0;
}