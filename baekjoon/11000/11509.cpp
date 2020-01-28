#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)

const int max_H = 1000000;
int arrow[max_H + 1];
int main()
{
    int N; scanf("%d", &N);
    int ans = 0;
    while (N--) {
        int h; scanf("%d", &h);
        // 해당 높이를 지나가는 화살이 있으면,풍선은 자동으로 터진다.
        if (arrow[h]) {
            --arrow[h];
            ++arrow[h - 1];
        }
        // 지나가는 화살이 없으면 화살을 하나 추가해야 한다.
        else {
            ++ans;
            ++arrow[h - 1];
        }
    }
    printf("%d", ans);
    return 0;
}