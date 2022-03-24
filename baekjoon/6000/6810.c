#include <stdio.h>

int main() {
    int sum = 91;
    for (int i = 1, x; ~scanf("%d", &x); i = 4 - i) {
        sum += x * i;
    }
    printf("The 1-3-sum is %d", sum);
}
