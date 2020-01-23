#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>

int N, mov[4][2] = { -1,0,1,0,0,-1,0,1 };
P Map[100][100];	//A나라, 길이 다리. 기본 길이 1
queue<P> q;

// 인접한 땅을 전부 num으로 채운다.
// num : 나라의 번호
void DFS(int r, int c, int num)
{
    Map[r][c].first = num;
    q.push(make_pair(r, c));
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= N || C < 0 || C >= N) continue;
        if (Map[R][C].second == 1 && Map[R][C].first == 0)
            DFS(R, C, num);
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> N;
    loop(i, N) loop(j, N)
        cin >> Map[i][j].second;
    int num_island = 0;
    loop(i, N) loop(j, N)
        if (Map[i][j].second == 1 && Map[i][j].first == 0)
            DFS(i, j, ++num_island);
    // Map[i][j].first : (i,j)칸의 나라
    // Map[i][j].second : 놓인 다리의 길이

    bool flag = 0;
    P Check;
    int ans = INT32_MAX;
    while (1) {
        int r = q.front().first, c = q.front().second; q.pop();
        int Nara = Map[r][c].first, brid = Map[r][c].second;
        
        if (flag && (Check.first != Nara || Check.second != brid)) break;
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= N || C < 0 || C >= N) continue;
            if (Map[R][C].first == 0) {
                Map[R][C] = make_pair(Nara, brid + 1);
                q.push(make_pair(R, C));
            }
            else if ((Map[R][C].first != Nara)) {
                ans = min(ans, brid + Map[R][C].second - 2);
                flag = true, Check = make_pair(Nara, brid);
            }
        }
    }
    cout << ans;
    return 0;
}