#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    int A, B, N;
    cin >> A >> B >> N;
    A %= B;	// A : 몫
    while (--N) {
        A *= 10;	// 몫을 * 10 하고
        A %= B;		// 몫의 몫을 취해줌
    }
    cout << A * 10 / B;
    return 0;
}