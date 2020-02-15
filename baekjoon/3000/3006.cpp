#include <bits/stdc++.h>
using namespace std;

const int max_N = 100000;

int N;
int pos[max_N + 1];
int fenwick[max_N + 1];

int read(int idx)
{
    int ret = 0;
    while (idx) {
        ret += fenwick[idx];
        idx -= (idx & -idx);
    }
    return ret;
}
void update(int idx)
{
    while (idx <= N) {
        --fenwick[idx];
        idx += (idx & -idx);
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> N;
    // pos[x] = 숫자 x가 위치한 index
    for (int i = 1; i <= N; ++i) {
        int x; cin >> x;
        pos[x] = i;
    }
    // 모든 요소가 1인 arr의 fenwick tree를 만든다.
    for (int i = 1; i <= N; ++i)
        fenwick[i] = i & -i;

    // idx = pos[X] ---- X가 위치한 index를 idx라고 하자.
    // 모든 요소가 1인 크기가 N짜리 arr가 있다고 할 때,
    // X를 왼쪽으로 옮기는 횟수는 idx 왼쪽의 구간합을 구하면 된다.
    // X를 오른쪽으로 옮기는 것도, idx 오른쪽의 구간합을 구하면 된다.
    // 옮긴 후에는 X를 0으로 바꾼다.
    for (int i = 0; i < N / 2; ++i) {
        int idx;
        idx = pos[1 + i];
        cout << read(idx - 1) << '\n';
        update(idx);
        idx = pos[N - i];
        cout << read(N) - read(idx) << '\n';
        update(idx);
    }
    if (N % 2) cout << read(pos[N / 2 + 1] - 1);
    return 0;
}