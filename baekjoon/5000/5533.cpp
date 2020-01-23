#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

// num : a학생이 b라운드에 고른 숫자
// cache : a라운드에 b숫자가 몇 번 나왔는지
int num[200][3], cache[3][101];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) loop(j, 3) {
        cin >> num[i][j];
        ++cache[j][num[i][j]];
    }
    loop(i, N) {
        int scr = 0;
        loop(j, 3)
            // 고른 숫자가 해당 라운드에 딱 1번만 나왔다면 합산
            if (cache[j][num[i][j]] == 1)
                scr += num[i][j];
        cout << scr << '\n';
    }
    return 0;
}