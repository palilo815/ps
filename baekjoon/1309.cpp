#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define MOD 9901

int main()
{
    cin.tie(NULL); cout.tie(NULL);
    std::ios::sync_with_stdio(false);

    int n;
    cin >> n;
    int zoo[2][3];	// 소중한 메모리 아끼자 >_<
    loop(i, 3)
        zoo[0][i] = 1;
    // zoo[i][0] : i번 칸에 사자 안넣음
    //		 [1] : i번 칸의 왼쪽에 넣음
    //		 [2] :         오른쪽에 넣음
    loop(i, n - 1) {
        int prev = i % 2, curr = 1 - prev;
        zoo[curr][0] = (zoo[prev][0] + zoo[prev][1] + zoo[prev][2]) % MOD;
        zoo[curr][1] = (zoo[prev][0] + zoo[prev][2]) % MOD;
        zoo[curr][2] = (zoo[prev][0] + zoo[prev][1]) % MOD;
    }
    int curr = 1 - (n % 2);
    cout << (zoo[curr][0] + zoo[curr][1] + zoo[curr][2]) % MOD;
    return 0;
}