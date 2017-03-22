#include <stdio.h>
#include <stdlib.h>

int n, i, k;

/**
 * N Queens problem:
 *
 * Construction methods:
 * @url http://penguin.ewu.edu/~trolfe/QueenLasVegas/Hoffman.pdf
 */
int main() {
    while (scanf("%d", &n) != EOF) {
        if (n == 0) break;

        // 1. n mod 6 != 2 and n mod 6 != 3
        //    e.g., n = 10, 11, 12, 13, 16, 17, ...
        // 1.1. n is even
        //    (2, 4, 6, 8, ..., n), (1, 3, 5, 7, ..., n-1)
        // 1.2. n is odd
        //    (2, 4, 6, 8, ..., n-1), (1, 3, 5, 7, ..., n)
        if (n % 6 != 2 && n % 6 != 3) {
            printf("2");
            for (i = 4; i <= n; i += 2) printf(" %d", i);
            for (i = 1; i <= n; i += 2) printf(" %d", i);
            printf("\n");
            continue;
        }

        // 2. n mod 6 == 2 or n mod 6 == 3
        //    e.g., n = 8, 9, 14, 15, ...
        //    1) if n is even, k = n / 2
        //    2) if n is odd, k = (n - 1) / 2
        k = n / 2;

        // 2.1. k is even, n is even
        //     (k, k+2, k+4, ..., n), (2, 4, ..., k-2), (k+3, k+5, ..., n-1), (1, 3, 5, ..., k+1)
        //     e.g., n = 8, k = 4
        // 2.2. k is even, n is odd
        //     (k, k+2, k+4, ..., n-1), (2, 4, ..., k-2), (k+3, k+5, ..., n-2), (1, 3, 5, ..., k+1, n)
        //     e.g., n = 9, k = 4
        // 2.3. k is odd, n is even
        //     (k, k+2, k+4, ..., n-1), (1, 3, 5, ..., k-2), (k+3, ..., n), (2, 4, ..., k+1)
        //     e.g., n = 10, k = 5
        // 2.4. k is odd, n is odd
        //     (k, k+2, k+4, ..., n-2), (1, 3, 5, ..., k-2), (k+3, ..., n-1), (2, 4, ..., k+1, n)
        //     e.g., n = 11, k = 5

        // 1st sequence
        printf("%d", k);
        for (i = k + 2; i < n; i += 2) printf(" %d", i);
        if (!(k & 1) && !(n & 1)) printf(" %d", n); // k is even, n is even

        // 2nd sequence
        // if k is odd, i starts from 1, else i starts from 2
        for (i = (k & 1) ? 1 : 2; i <= k - 2; i += 2) printf(" %d", i);

        // 3rd sequence
        for (i = k + 3; i < n; i += 2) printf(" %d", i);
        if ((k & 1) && !(n & 1)) printf(" %d", n); // k is odd, n is even

        // 4th sequence
        // if k is odd, i starts from 2, else i starts from 1
        for (i = (k & 1) ? 2 : 1; i <= k + 1; i += 2) printf(" %d", i);
        if (n & 1) printf(" %d", n); // n is odd

        printf("\n");
    }

    return 0;
}
