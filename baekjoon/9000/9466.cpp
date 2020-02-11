#include <bits/stdc++.h>
using namespace std;

const int max_N = 100000;

int choice[max_N + 1];
int team[max_N + 1];

int DFS(int u)
{
    if (team[u] == 2) return u;
    else if (team[u] == 1 || team[u] == -1) return -1;

    team[u] = 2;
    int ret = DFS(choice[u]);
    team[u] = (ret == -1 ? -1 : 1);
    if (ret == u) ret = -1;
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        memset(team, 0, sizeof(team));
        for (int i = 1; i <= N; ++i) {
            cin >> choice[i];
            if (i == choice[i]) team[i] = 1;
        }
        /*
            team == 1 : 팀을 완성한 경우
            team == -1: 팀을 만드는게 불가능한 경우
            team == 0 : 아직 모르는 경우
            
            team == 2 : 탐색중인 경우
            DFS를 사용해서, 자기 팀을 2로 만들고, 내가 선택한 사람으로 재귀호출을 한다.
            만약 DFS가 계속 전진하다가 1 or -1을 만나는 경우, DFS가 지나온 애들은 팀을 꾸릴 수 없다.
            만약 2를 만나는경우, 사이클이 생겼다는 의미이고, 이 사이클에 속하는 애들은 팀을 꾸릴 수 있다.

            DFS함수는 위의 경우 -1을 리턴하고, 아래의 경우 사이클이 생긴 노드의 번호를 리턴한다.
        */
        int ans = 0;
        for (int i = 1; i <= N; ++i) {
            if (!team[i]) DFS(i);
            if (team[i] == -1) ++ans;
        }
        cout << ans << '\n';
    }
    return 0;
}