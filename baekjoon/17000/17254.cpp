#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define T tuple<int,int,char>
using namespace std;
const int max_M = 1000;

T board[max_M];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // 입력되는 N은 쓸모가 없다.
    int M; cin >> M >> M;
    int num, second;
    char key;
    loop(i, M) {
        cin >> num >> second >> key;
        board[i] = { second,num,key };
    }
    sort(board, board + M);
    loop(i, M)
        cout << get<2>(board[i]);
    return 0;
}