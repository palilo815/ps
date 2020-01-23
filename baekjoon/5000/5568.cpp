#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

set<int> cache; // 만든 숫자 저장
vector<int> card_idx; // 선택한 카드의 index 저장
int N, card[10][2]; // card[i][0] : i번 카드의 숫자, card[i][1] : 10^숫자의 자릿수  
bool selected[10];

// k개의 숫자를 뽑는 함수
void make_num(int k)
{
    // k개를 전부 골랐으면
    if (k == 0) {
        // vector에 저장된 순서대로 num을 만든다.
        int num = 0;
        for (int idx : card_idx) {
            num *= card[idx][1];
            num += card[idx][0];
        }
        // 만든 숫자 저장
        cache.insert(num);
        return;
    }

    // 고를 카드가 남았으면
    loop(i, N)
        if (!selected[i]) {
            selected[i] = true;
            card_idx.push_back(i);
            make_num(k - 1);
            selected[i] = false;
            card_idx.pop_back();
        }
}
int main()
{
    int K; cin >> N >> K;
    loop(i, N) {
        cin >> card[i][0];
        card[i][1] = card[i][0] < 10 ? 10 : 100;
    }
    make_num(K);
    cout << cache.size();
    return 0;
}