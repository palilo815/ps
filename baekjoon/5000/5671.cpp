#include <stdio.h>
#include <string.h>
const int max_N = 5000;

int psum[max_N + 1];
bool used[10];
bool dup_num(int n)
{
    memset(used, 0, sizeof(used));
    while (n) {
        int x = n % 10;
        if (used[x]) return true;
        used[x] = true;
        n /= 10;
    }
    return false;
}
int main()
{
    for (int i = 1; i <= 5000; ++i) {
        if (dup_num(i)) psum[i] = psum[i - 1];
        else psum[i] = psum[i - 1] + 1;
    }
    int a, b;
    while (scanf("%d %d", &a, &b) != -1)
        printf("%d\n", psum[b] - psum[a - 1]);
    return 0;
}