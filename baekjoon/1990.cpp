#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

// Prime & Pallindrome
// len이 1,2인건 따로 직접 넣었음
vector<int> PP = { 2, 3, 5, 7, 11 };

// number의 l,r자리를 채울 차례
// P & P인 경우는 len이 홀수인 경우만 가능하다 (11제외)
void pallin(int l, int r, int number)
{
    // 모든 자리를 채운 경우 소수인지 판별해서 vector에 넣음
    if (l == r) loop(i, 10) {
        int tmp = number + i * l;
        if (tmp == 1 || tmp % 2 == 0) goto OUT;
        for (int j = 3; j * j <= tmp; j += 2)
            if (tmp % j == 0) goto OUT;
        PP.push_back(tmp);
    OUT:;
    }
    // 아니면 재귀호출
    else loop(i, 10) {
        if (r == 1 && i == 0) continue;
        int tmp = number + l * i + r * i;
        pallin(l / 10, r * 10, tmp);
    }
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int a, b; cin >> a >> b;
    int len_a = 0, len_b = 0;

    // a와 b의 자릿수를 구해준다. 
    int tmp = a;
    while (tmp)
        tmp /= 10, ++len_a;
    // len = 1,2인 경우는 직접 넣어줬으므로 패스
    len_a = max(len_a, 3);
    if (len_a % 2 == 0) ++len_a;
    tmp = b;
    while (tmp)
        tmp /= 10, ++len_b;

    for(int len = len_a; len <= len_b; len += 2)
        pallin(pow(10, len - 1), 1, 0);
    for (int x : PP) if (x >= a && x <= b)
        cout << x << '\n';
    cout << -1;
    return 0;
}