#include <stdio.h>
#include <stdlib.h>

double len;

int main() {
    register int i;
    scanf("%lf", &len);

    while (len != 0.0f) {
        i = 2;
        while (len > 0) {
            len -= (1.00f / (double) i);
            ++i;
        }
        printf("%d card(s)\n", i - 2);

        scanf("%lf", &len);
    }

    return 0;
}
