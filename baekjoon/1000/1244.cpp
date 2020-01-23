#include <iostream>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;

bool swch[101];
int main()
{
    int N; cin >> N;
    LOOP(i, N) cin >> swch[i];
    int M; cin >> M;
    while (M--) {
        int sex, num; cin >> sex >> num;
        if (sex == 1)
            for (int i = num;i <= N;i += num)
                swch[i] = !swch[i];
        else {
            swch[num] = !swch[num];
            int l = num - 1, r = num + 1;
            while (0 < l && r <= N && swch[l] == swch[r]) {
                swch[l] = !swch[l];
                swch[r] = !swch[r];
                --l, ++r;
            }
        }
    }
    LOOP(i, N) {
        cout << swch[i] << ' ';
        if (i % 20 == 0) cout << '\n';
    }
    return 0;
}