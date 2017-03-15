#include <stdio.h>

#define MAX_LENGTH (32 + 8 + 1)
#define INPUT_LIMIT 10000000

int n, dup;
int telNumbers[INPUT_LIMIT];
int mapint[25] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 0, 7, 7, 8, 8, 8, 9, 9, 9};

int main() {
    register int i, j, num;
    register int k;
    register char c;

    scanf("%d\n", &n);

    // Input
    for (i = 0; i < n; ++i) {
        for (num = 0, j = 0; j < 7;) {
            c = getchar();
            if (c >= '0' && c <= '9') {
                num = num * 10 + (c - '0');
                ++j;
            } else if (c >= 'A' && c <= 'Y' && c != 'Q') {
                num = num * 10 + mapint[c - 'A'];
                ++j;
            }
        }
        ++telNumbers[num];

        // Remaining characters
        while (getchar() != '\n') ;
    }

    // Output
    for (i = 0; i < 10000000; ++i) {
        k = telNumbers[i];
        if (k > 1) {
            printf("%03d-%04d %d\n", i / 10000, i % 10000, k);
            dup = 1;
        }
    }
    if (!dup) printf("No duplicates.\n");

    return 0;
}
