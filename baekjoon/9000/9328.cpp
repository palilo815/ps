#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;

int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
// 맵의 외곽을 전부 빈 공간으로 채울 것이므로 102*102크기로 만든다.
char M[102][102];
bool visited[102][102];
// 해당 알파벳의 열쇠를 가지고 있는지 여부
bool keys[26];
// 열지 못한 문의 좌표 저장
vector<P> door[26];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T, row, col; cin >> T;
    while (T--) {
        // ** initialize **
        // 맵 초기화에서 memset(0)을 하므로, '.'는 0으로 바꾼다.
        cin >> row >> col;
        for (int i = 1;i <= row;++i)
            for (int j = 1;j <= col;++j) {
                char c; cin >> c;
                if (c != '.') M[i][j] = c;
            }
        // 처음 받는 열쇠
        string key; cin >> key;
        if (key != "0")
            for (char c : key)
                keys[c - 'a'] = true;
        
        // ** BFS **
        // (0,0)에서 시작한다.
        queue<P> q;
        q.push({ 0,0 });
        visited[0][0] = true;
        int ans = 0;
        while (!q.empty()) {
            int r = q.front().first, c = q.front().second; q.pop();

            // 문서를 찾으면 ans 증가
            if (M[r][c] == '$') {
                ++ans;
                M[r][c] = 0;
            }
            // 열쇠를 찾으면 keys[]를 true로 바꾸고
            // door[]의 좌표를 전부 queue에 집어넣는다.
            else if (M[r][c] >= 'a' && M[r][c] <= 'z') {
                int key_num = M[r][c] - 'a';
                keys[key_num] = true;
                for (P p : door[key_num]) {
                    q.push(p);
                    visited[p.first][p.second] = true;
                }
                door[key_num].clear();
                M[r][c] = 0;
            }
            
            // 아직 방문 안한 칸 중
            // visited or '*' : 무조건 못 감
            // 대문자 : 열쇠가 있어야 감
            // 소문자 & 0 : 무조건 갈 수 있음
            loop(i, 4) {
                int R = r + mov[i][0], C = c + mov[i][1];
                // visited or '*'
                if (R < 0 || R > row + 1 || C < 0 || C > col + 1 || visited[R][C] || M[R][C] == '*') continue;
                // 대문자 && 열쇠도 없음
                // door에 저장했다가, 나중에 열쇠를 찾으면 방문한다.
                if (M[R][C] >= 'A' && M[R][C] <= 'Z' && !keys[M[R][C] - 'A'])
                    door[M[R][C] - 'A'].push_back({ R,C });
                // 그 이외에는 방문 가능
                else {
                    q.push({ R,C });
                    visited[R][C] = true;
                }
            }
        }
        loop(i, 26) door[i].clear();
        memset(M, 0, sizeof(M));
        memset(visited, 0, sizeof(visited));
        memset(keys, 0, sizeof(keys));
        cout << ans << '\n';
    }
    
    return 0;
}