#include <stdio.h>

int main() {
    if ((getchar() & ~32) == 'N') {
        puts("Naver D2");
    } else {
        puts("Naver Whale");
    }
}
