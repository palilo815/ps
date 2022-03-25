#include <math.h>
#include <stdio.h>

int main() {
    int w, h;
    scanf("%d%d", &w, &h);
    printf("%.9lf", w + h - sqrt(w * w + h * h));
}
