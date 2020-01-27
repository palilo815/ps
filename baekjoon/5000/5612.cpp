#include <stdio.h>

int main()
{
    int T, car, in, out;
    scanf("%d %d", &T, &car);
    int max_car = car;
    while (T--) {
        scanf("%d %d", &in, &out);
        car += in - out;
        if (car < 0) {
            max_car = 0;
            break;
        }
        else if (car > max_car)
            max_car = car;
    }
    printf("%d", max_car);
    return 0;
}