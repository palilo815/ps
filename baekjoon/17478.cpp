#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

string Q[4] =
{ "\"재귀함수가 뭔가요?\"",
"\"잘 들어보게. 옛날옛날 한 산 꼭대기에 이세상 모든 지식을 통달한 선인이 있었어.",
"마을 사람들은 모두 그 선인에게 수많은 질문을 했고, 모두 지혜롭게 대답해 주었지.",
"그의 답은 대부분 옳았다고 하네. 그런데 어느 날, 그 선인에게 한 선비가 찾아와서 물었어.\"" };
string A[2] =
{ "\"재귀함수가 뭔가요?\"",
"\"재귀함수는 자기 자신을 호출하는 함수라네\"" };
string E = "라고 답변하였지.";

void rec(int n, int space)
{
    if (n) {
        loop(i, 4)
            cout << '\n' << string(space, '_') << Q[i];
        rec(n - 1, space + 4);
    }
    else {
        loop(i, 2)
            cout << '\n' << string(space, '_') << A[i];
    }
    cout << '\n' << string(space, '_') << E;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    cout << "어느 한 컴퓨터공학과 학생이 유명한 교수님을 찾아가 물었다.";
    rec(N, 0);
    return 0;
}