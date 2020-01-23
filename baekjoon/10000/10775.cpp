#include <iostream>
using namespace std;

// 해당 gate를 지나친 비행기의 숫자
int passed[100001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int G, P; cin >> G >> P;
    int ans = 0;
    bool failed = false;
    while (P-- && !failed) {
        int gate; cin >> gate;
        
        // passed[gate] == n이라면,
        // n개의 비행기가 이미 도킹을 시도한 적이 있단 뜻이다.
        // 따라서 gate부터 gate-n까지의 게이트에는 절대 자리가 있을 수 없다.
        while (gate > 0 && passed[gate] > 0) {
            int mov = passed[gate]++;
            gate -= mov;
        }

        // gate 번호는 1부터 시작이다.
        // 0이하의 gate는 실패했단 뜻이다.
        if (gate <= 0) failed = true;
        else {
            ++ans;
            passed[gate] = 1;
        }
    }
    cout << ans;
    return 0;
}