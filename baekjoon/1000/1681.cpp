#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int L;
bool Check(int n)
{
    while (n) {
        if (n % 10 == L) return true;
        n /= 10;
    }
    return false;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, cnt = 0;
    cin >> n >> L;
    for (int i = 1; ; ++i) {
        // i를 학생에게 줄 수 없는 경우 continue
        if (Check(i)) continue;
        // i를 학생에게 준다.
        // 만약 n명에게 모두 주었다면 i가 마지막 수
        if (++cnt == n) { cout << i; break; }
    }
    return 0;
}