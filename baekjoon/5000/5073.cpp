#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int a[3];
    while (1) {
        loop(i, 3) cin >> a[i];
        if (a[0] == 0) break;
        sort(a, a + 3);
        // 가장 긴 변이 나머지 둘의 합보다 크면 불가능
        if (a[2] >= a[0] + a[1]) cout << "Invalid\n";
        else {
            // 정렬되었기 때문에 a[0]==a[2]이면 a[0]==a[1]==a[2]
            if (a[0] == a[2]) cout << "Equilateral\n";
            // 두 개만 같으면 이등변
            else if (a[0] == a[1] || a[1] == a[2]) cout << "Isosceles\n";
            // 전부 아닌 경우
            else cout << "Scalene\n";
        }
    }
    return 0;
}