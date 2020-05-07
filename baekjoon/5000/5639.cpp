#include <bits/stdc++.h>
using namespace std;

int pre_order[10000];

void print_post(int l, int r) {
    if (l == r) return;
    int rt = pre_order[l];
    int R_sub = upper_bound(pre_order + l, pre_order + r, rt) - pre_order;
    print_post(l + 1, R_sub);
    print_post(R_sub, r);
    cout << pre_order[l] << '\n';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int n, sz = 0;
    while (cin >> n)
        pre_order[sz++] = n;

    print_post(0, sz);
    return 0;
}