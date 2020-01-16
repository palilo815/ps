#include<iostream>
using namespace std;

int main()
{
    int n; cin >> n;
    
    // score : 문제 맞히면 얻는 점수
    // total : 총 점수 합
    int score = 1, total = 0;
    while (n--) {
        int x; cin >> x;
        // 맞히면 score만큼 획득, score 1증가
        if (x) total += score++;
        // 틀리면 score 1로 초기화
        else score = 1;
    }
    cout << total;
    return 0;
}