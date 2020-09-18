#include <cstdio>

int main() {
    long long N;
    scanf("%lld", &N);
    N %= 7;
    puts((N == 0 || N == 2) ? "CY" : "SK");
    return 0;
}