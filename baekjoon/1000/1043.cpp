#include <iostream>
#include <vector>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int MAX = 50;

vector<int> party[MAX]; // party[i] : i번 파티의 참석자 명단
bool tell_truth[MAX];   // tell_truth[i] : i번 파티에서 진실을 말해야만 하는지 여부
bool witness[MAX + 1];  // witness[i] : i번 사람이 진실을 알고 있는지 여부

int main() {
    int N, M, K; cin >> N >> M >> K;
    loop(i, K) {
        int x; cin >> x;
        witness[x] = true;
    }
    loop(i, M) {
        int cnt; cin >> cnt;
        while (cnt--) {
            int x; cin >> x;
            party[i].push_back(x);
        }
    }

    bool update = true;
    while (update) {
        update = false;
        loop(i, M) if (!tell_truth[i]) {
            bool flag = false;
            for (int x : party[i]) if (witness[x]) {
                flag = true;
                break;
            }
            if (flag) {
                tell_truth[i] = true;
                update = true;
                for (int x : party[i])
                    witness[x] = true;
            }
        }
    }
    
    int ans = 0;
    loop(i, M) if (!tell_truth[i])
        ++ans;
    cout << ans;
    return 0;
}