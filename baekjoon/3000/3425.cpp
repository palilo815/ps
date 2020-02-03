#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;
const int max_inst = 100000;

class go_stack {

private:
    const int go_max = 1000000000;
    const int go_min = -1000000000;
    int stk[1000];
    int len;

public:
    bool NUM(int x) {
        stk[len++] = x;
        return true;
    }
    bool POP() {
        if (len == 0) return false;
        --len;
        return true;
    }
    bool INV() {
        if (len == 0) return false;
        stk[len - 1] = -stk[len - 1];
        return true;
    }
    bool DUP() {
        if (len == 0) return false;
        stk[len] = stk[len - 1];
        ++len;
        return true;
    }
    bool SWP() {
        if (len < 2) return false;
        swap(stk[len - 1], stk[len - 2]);
        return true;
    }
    bool ADD() {
        if (len < 2) return false;
        int res = stk[len - 1] + stk[len - 2];
        if (res < go_min || res > go_max) return false;
        stk[len - 2] = res;
        --len;
        return true;
    }
    bool SUB() {
        if (len < 2) return false;
        int res = stk[len - 2] - stk[len - 1];
        if (res < go_min || res > go_max) return false;
        stk[len - 2] = res;
        --len;
        return true;
    }
    bool MUL() {
        if (len < 2) return false;
        ll res = ll(stk[len - 1]) * stk[len - 2];
        if (res < go_min || res > go_max) return false;
        stk[len - 2] = res;
        --len;
        return true;
    }
    bool DIV() {
        if (len < 2 || stk[len - 1] == 0) return false;
        int res = stk[len - 2] / stk[len - 1];
        stk[len - 2] = res;
        --len;
        return true;
    }
    bool MOD() {
        if (len < 2 || stk[len-1] == 0) return false;
        int res = stk[len - 2] % stk[len - 1];
        stk[len - 2] = res;
        --len;
        return true;
    }
    int answer() {
        if (len != 1) return INT_MIN;
        return stk[0];
    }
    void clear() {
        len = 0;
    }
};
bool wrapper(go_stack& gtk, int x)
{
    switch (x) {
    case -1: return gtk.POP();
    case -2: return gtk.INV();
    case -3: return gtk.DUP();
    case -4: return gtk.SWP();
    case -5: return gtk.ADD();
    case -6: return gtk.SUB();
    case -7: return gtk.MUL();
    case -8: return gtk.DIV();
    case -9: return gtk.MOD();
    default: return gtk.NUM(x);
    }
}

int inst[max_inst];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);
START:;

    string s;
    int N_inst = 0;

    // ** instruction이 저장되는 구조는 wrapper 참고 **
    while (1) {
        cin >> s;
        if (s[0] == 'Q') return 0;
        if (s[0] == 'E') break;
        if (s[0] == 'N') {
            int x; cin >> x;
            inst[N_inst] = x;
        }
        else if (s[0] == 'P') inst[N_inst] = -1;
        else if (s[0] == 'I') inst[N_inst] = -2;
        else if (s[0] == 'D') {
            if (s[1] == 'U') inst[N_inst] = -3;
            else inst[N_inst] = -8;
        }
        else if (s[0] == 'S') {
            if (s[1] == 'W') inst[N_inst] = -4;
            else inst[N_inst] = -6;
        }
        else if (s[0] == 'A') inst[N_inst] = -5;
        else {
            if (s[1] == 'U') inst[N_inst] = -7;
            else inst[N_inst] = -9;
        }
        ++N_inst;
    }

    go_stack gtk;
    int N; cin >> N;
    while (N--) {
        gtk.clear();
        bool error = false;
        int init; cin >> init;
        gtk.NUM(init);

        // N_inst개의 instruction 중 한 개라도 false가 되면 중단한다.
        loop(i, N_inst)
            if (!wrapper(gtk, inst[i])) {
                error = true;
                break;
            }

        // answer()는 스택에 값이 하나라면 그 값을 리턴, 아니라면 INT_MIN 리턴
        if (error || gtk.answer() == INT_MIN) cout << "ERROR\n";
        else cout << gtk.answer() << '\n';
    }
    cout << '\n';

    // QUIT가 입력될 때 까지 반복한다.
    goto START;
    return 0;
}