#include <stdio.h>
#include <stdlib.h>
long DIVIDE(int A, int B, int C)
{
    if (B == 1)
        return A % C;
    else if (B % 2 == 0) {
        long val = DIVIDE(A, B / 2, C);
        return ((val % C) * (val % C)) % C;
    }
    else {
        long val = DIVIDE(A, B / 2, C);
        long val2 = ((((val % C) * (val % C)) % C) * ((A % C) % C)) % C;
        return val2;
    }
}
int main()
{
    long A, B, C;
    scanf("%ld %ld %ld", &A, &B, &C);

    long val = DIVIDE(A, B, C);
    printf("%ld", val);
    return 0;
}