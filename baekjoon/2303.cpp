#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)


int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int card[5], N, max_score = 0, max_id;
    cin >> N;
    loop(n, N) {
        loop(i, 5) cin >> card[i];
        int score = 0;
        loop(i, 3) for (int j = i + 1;j < 4;++j) for (int k = j + 1;k < 5;++k)
            score = max(score, (card[i] + card[j] + card[k]) % 10);
        if (score >= max_score) {
            max_score = score;
            max_id = n + 1;
        }
    }
    cout << max_id;
    return 0;
}