#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL); cout.tie(NULL);
    std::ios::sync_with_stdio(false);

    int n;
    while (cin >> n) {
        if (n == 0) break;
        // Ans : 정답 저장, tmp : 입력받는 n개의 str을 임시로 저장
        // index 0에는 str 원형 저장
        // index 1에는 소문자로 바꿔서 저장
        // 따라서 대소 비교는 index1로, 정답 출력은 index0으로 한다.
        string Ans[2], tmp[2];
        Ans[1] = "z";
        while (n--) {
            cin >> tmp[0];
            tmp[1] = tmp[0];
            loop(i, tmp[1].size())
                if (tmp[1][i] > 'Z')
                    tmp[1][i] -= 32;
            if (tmp[1] < Ans[1])
                Ans[1] = tmp[1], Ans[0] = tmp[0];
        }
        cout << Ans[0] << '\n';
    }
    return 0;
}