#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

char seat[50];
int main()
{
    int N, ans = 0;
    cin >> N;
    loop(i, N) cin >> seat[i];
    bool flag = true; // 여유분이 딱 하나 있다.

    // 싱글은 무조건 왼쪽 홀더를 사용한다.
    // 어쩔 수 없이 오른쪽을 사용하게 되면, flag를 false로 바꾼다.
    // 이때부턴 무조건 오른쪽만 사용 가능하다.
    loop(i, N) {
        // 싱글은 무조건 사용 가능.
        if (seat[i] == 'S') ++ans;
        // 커플은 flag == true이면, 양쪽 다 사용 가능
        else {
            if (flag) ++ans;
            ++ans, ++i;
            flag = false;
        }
    }
    cout << ans;
    return 0;
}