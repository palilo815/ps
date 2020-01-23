#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

void count_love(string& s, int(&arr)[4])
{
    memset(arr, 0, sizeof(arr));
    int len = s.size();
    loop(i, len) {
        char c = s[i];
        if (c == 'L') ++arr[0];
        else if (c == 'O') ++arr[1];
        else if (c == 'V') ++arr[2];
        else if (c == 'E') ++arr[3];
    }
}
int calc_love(int(&A)[4], int(&B)[4])
{
    int LOVE[4], ret = 1;
    loop(i, 4) LOVE[i] = A[i] + B[i];
    for (int i = 0; i < 3; ++i)
        for (int j = i + 1; j < 4; ++j)
            ret *= (LOVE[i] + LOVE[j]);
    return ret % 100;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string me, girl, GF;
    int love = -1, n, L_me[4], L_girl[4];
    cin >> me >> n;
    // L_me : 내 이름의 L,O,V,E 개수
    count_love(me, L_me);

    // 가장 높은 궁합 수치는 love에 저장됨
    // love보다 높은 수치의 여자애가 등장하면 GF를 그 애로 바꿈
    while (n-- > 0) {
        cin >> girl;
        // L_girl : 여자애 이름의 L,O,V,E 개수
        count_love(girl, L_girl);
        int tmp = calc_love(L_me, L_girl);

        // 더 높은 애 등장하면 여친 바꾼다
        if (tmp > love) {
            love = tmp;
            GF = girl;
        }

        // 똑같은 수치면 사전순으로
        else if (tmp == love)
            if (girl < GF)
                GF = girl;
    }
    cout << GF;
    return 0;
}