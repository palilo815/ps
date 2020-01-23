#include <stdio.h>

int main()
{
    for (int a = 2; a <= 100; ++a) {
        int A = a * a * a;
        for (int b = 2; b < a; ++b) {
            int B = b * b * b;
            for (int c = b; c < a; ++c) {
                int C = c * c * c;
                if (A <= B + C) break;
                for (int d = c; d < a; ++d) {
                    int D = d * d * d;
                    if (A < B + C + D) break;
                    if (A == B + C + D)
                        printf("Cube = %d, Triple = (%d,%d,%d)\n", a, b, c, d);
                }
            }
        }
    }
    return 0;
}