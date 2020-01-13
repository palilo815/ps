#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int Tour[36];
bool visited[6][6];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // Tour에 이동 좌표 순서대로 저장
    loop(i, 36) {
        char r, c;
        cin >> r >> c;
        Tour[i] = (r - 'A') * 10 + (c - '1');
    }

    // (firR, firC) : 맨 처음 위치
    // 마지막 위치에서 처음 위치로 올 수 있어야함
    int r = Tour[0] / 10, c = Tour[0] % 10;
    int firR = r, firC = c;
    visited[r][c] = true;

    // valid 여부
    bool V = true;

    for (int i = 1; i < 36; ++i) {
        // (R,C) : 이동 후 위치
        int R = Tour[i] / 10, C = Tour[i] % 10;

        // 이미 이동할 위치를 방문한 경우
        // 이동할 위치로 나이트가 이동할 수 없는 경우 invalid로 만듦
        if (visited[R][C]) { V = false; break; }
        visited[R][C] = true;
        if (abs(R - r) == 2) {
            if (abs(C - c) != 1) { V = false; break; }
        }
        else if (abs(R - r) == 1) {
            if (abs(C - c) != 2) { V = false; break; }
        }
        else { V = false; break; }
        r = R, c = C;
    }

    // 마지막 위치에서 처음 위치로 갈 수 있는지 체크
    if (abs(firR - r) == 2) {
        if (abs(firC - c) != 1) V = false;
    }
    else if (abs(firR - r) == 1) {
        if (abs(firC - c) != 2) V = false;
    }
    else V = false;

    if (V) cout << "Valid";
    else cout << "Invalid";
    return 0;
}