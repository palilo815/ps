#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 100;
const int apple = -1;
const int body = 1;
const int mov[4][2] = { 0,1,1,0,0,-1,-1,0 }; // R D L U

int board[max_N][max_N];

class snake {
private:
    deque<p> path;
    int d, N;
public:
    snake(int N) {
        this->N = N;
        this->d = 0;
        path.emplace_back(0, 0);
    }
    bool move(){
        const auto [hr, hc] = path.back();
        const int HR = hr + mov[d][0];
        const int HC = hc + mov[d][1];
        if (HR < 0 || HR >= N || HC < 0 || HC >= N)
            return false;

        int tr, tc;
        switch (board[HR][HC]) {
        case body:
            return false;
        case NULL:
            tie(tr,tc) = path.front();
            board[tr][tc] = NULL;
            path.pop_front();
        case apple:
            path.emplace_back(HR, HC);
            board[HR][HC] = body;
        }
        return true;
    }
    void turn(const char c) {
        if (c == 'L') d = (d + 3) % 4;
        else d = (d + 1) % 4;
    }
};
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, K; cin >> N >> K;
    while (K--) {
        int r, c; cin >> r >> c;
        board[r - 1][c - 1] = apple;
    }

    snake bam(N);
    int _time = 0, t;
    char d;

    int Q; cin >> Q;
    while (Q--) {
        cin >> t >> d;
        while (_time < t) {
            ++_time;
            if (!bam.move()) {
                cout << _time;
                return 0;
            }
        }
        bam.turn(d);
    }
    while (1) {
        ++_time;
        if (!bam.move()) break;
    }
    cout << _time;
    return 0;
}