#include <stdio.h>

int main() {
    const char winner[][13] = {
        "ITMO",
        "SPbSU",
        "SPbSU",
        "ITMO",
        "ITMO",
        "SPbSU",
        "ITMO",
        "ITMO",
        "ITMO",
        "ITMO",
        "ITMO",
        "PetrSU, ITMO",
        "SPbSU",
        "SPbSU",
        "ITMO",
        "ITMO",
        "ITMO",
        "ITMO",
        "SPbSU",
        "ITMO",
        "ITMO",
        "ITMO",
        "ITMO",
        "SPbSU",
        "ITMO",
    };
    int y;
    scanf("%d%d", &y);
    puts(winner[y - 1995]);
}
