#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

// return 10^(max(a,b)의 자릿수 - 1)
// ex) a = 54321, b = 123이면 return 10000
int pow_10(int a, int b)
{
    int ret = 1;
    while (a || b) {
        ret *= 10;
        a /= 10, b /= 10;
    }
    return ret / 10;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int L, R;
    cin >> L >> R;

    int pivot = pow_10(L, R);
    int ans = 0;
    bool same_val = true;
    while (pivot && same_val) {
        int l = L / pivot, r = R / pivot;

        if (l == r) {
            // 만약 l과 r이 둘 다 8이면, 
            // ld이상 r이하를 만들기 위해 무조건 8을 써야한다.
            if (l == 8) ++ans;
        }

        // 만약 둘 중 하나라도 8이 아니면
        // 이후의 값은 8을 전혀 안쓰고 만들 수 있음
        else same_val = false;
        L %= pivot, R %= pivot;
        pivot /= 10;
    }
    cout << ans;
    return 0;
}