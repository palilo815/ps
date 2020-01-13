#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    loop(T, 3) {
        int n, bucket = 0;
        ll tmp, sum = 0, Num;
        cin >> n;

        while (n--) {
            cin >> Num;
            tmp = sum + Num;
            // overflow가 일어난 경우
            // 바가지가 넘쳤다
            if (sum > 0 && Num > 0 && tmp < 0) ++bucket;
            // 바가지가 없어졌다(?)
            if (sum < 0 && Num < 0 && tmp>0) --bucket;
            sum = tmp;
        }
        // overflow가 일어난 경우
        // 바가지의 부호가 정답
        if (bucket > 0) cout << '+';
        else if (bucket < 0) cout << '-';

        else {
            // 일어나지 않았다면 sum의 부호가 정답
            if (sum > 0) cout << '+';
            else if (sum < 0) cout << '-';
            else cout << 0;
        }
        cout << '\n';
    }
    return 0;
}