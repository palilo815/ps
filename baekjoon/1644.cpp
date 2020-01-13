#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool sieve[4000001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    vector<int> prime;
    int N; cin >> N;
    if (N == 1) { cout << 0; return 0; }
    for (int i = 2;i <= N;++i)
        if (!sieve[i]) {
            prime.push_back(i);
            for (int j = i * 2;j <= N;j += i)
                sieve[j] = true;
        }

    // two-pointer
    auto it1 = prime.begin();
    auto it2 = it1;
    int psum = *it1, ans = 0;
    while (1) {
        // l포인터 전진
        if (psum > N)
            psum -= *(it1++);
        // r포인터 전진
        else if (psum < N) {
            if (++it2 == prime.end()) break;
            psum += *it2;
        }
        // 정답 추가하고, l포인터 전진
        else {
            ++ans;
            psum -= *(it1++);
        }
    }
    cout << ans;
    return 0;
}