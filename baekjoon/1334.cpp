#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s; cin >> s;
    // special case : 숫자가 전부 9일 경우
    bool all9 = true;
    for (int i = 0; i < s.length(); ++i)
        if (s[i] != '9') {
            all9 = false;
            break;
        }
    // 전부 9인 경우 : 1000001 같은 수를 만듦
    if (all9) {
        cout << '1' << string(s.length() - 1, '0') << '1';
        return 0;
    }


    bool bigger = false;
    int L = 0, R = s.length() - 1;
    // 숫자를 팰린드롬으로 만드는데,
    // 오른쪽 숫자를 왼쪽 숫자로 바꾼다.
    while (L < R) {
        if (s[L] > s[R]) bigger = true;
        else if (s[L] < s[R]) bigger = false;
        s[R] = s[L];
        L++, R--;
    }
    // bigger == true면 바뀌기 전 숫자보다 커졌단 뜻

    // 만약 커지지 않은 경우, 가장 중간 자리를 1 증가시킴,
    if (!bigger) {
        // 중간 자리가 1개일 경우
        if (L == R) {
            s[L]++;
            while (s[L] > '9') {
                s[L] = '0', s[R] = '0';
                L--, R++;
                s[L]++, s[R]++;
            }
        }
        // 길이가 짝수라 중간 자리가 2개인 경우
        else {
            L--, R++;
            s[L]++, s[R]++;
            while (s[L] > '9') {
                s[L] = '0', s[R] = '0';
                L--, R++;
                s[L]++, s[R]++;
            }
        }
    }
    cout << s;
    return 0;
}