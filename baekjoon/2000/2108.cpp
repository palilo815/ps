#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int arr[8001];

int main() {
    int N; scanf("%d", &N);
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        int x; scanf("%d", &x);
        sum += x;
        ++arr[x + 4000];
    }

    if (sum > 0) sum = 1.0 * sum / N + 0.5;
    else if (sum < 0) sum = 1.0 * sum / N - 0.5;

    int l = 0, r = 8000;
    while (!arr[l]) ++l;
    while (!arr[r]) --r;

    int rep = -1, mid = 0, cnt = 0;;
    bool is_second = false, find_mid = false;

    for (int i = l; i <= r; ++i) {
        cnt += arr[i];

        if (rep == -1 || arr[i] > arr[rep]) {
            rep = i;
            is_second = false;
        }
        else if (arr[i] == arr[rep] && !is_second) {
            rep = i;
            is_second = true;
        }

        if (cnt >= (N + 1) / 2 && !find_mid) {
            mid = i;
            find_mid = true;
        }
    }
    
    printf("%d\n%d\n%d\n%d", sum, mid - 4000, rep - 4000, r - l);
    return 0;
}