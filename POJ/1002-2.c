#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH (32 + 8 + 1)

int cmp(const void *p1, const void *p2) {
    return strcmp(*((char **) p1), *((char **) p2));
}

char *toStandardForm(char *s) {
    char *buf = (char *) malloc(sizeof(char) * 9);
    buf[8] = '\0'; // Last, NULL-terminated
    buf[7] = '\0';

    for (char *p = s, *q = buf; *p != '\0'; ++p) {
        if (q - buf == 3) {
            *q = '-';
            ++q;
        }

        switch (*p) {
            case 'A':
            case 'B':
            case 'C':
                *q = '2';
                ++q;
                break;
            case 'D':
            case 'E':
            case 'F':
                *q = '3';
                ++q;
                break;
            case 'G':
            case 'H':
            case 'I':
                *q = '4';
                ++q;
                break;
            case 'J':
            case 'K':
            case 'L':
                *q = '5';
                ++q;
                break;
            case 'M':
            case 'N':
            case 'O':
                *q = '6';
                ++q;
                break;
            case 'P':
            case 'R':
            case 'S':
                *q = '7';
                ++q;
                break;
            case 'T':
            case 'U':
            case 'V':
                *q = '8';
                ++q;
                break;
            case 'W':
            case 'X':
            case 'Y':
                *q = '9';
                ++q;
                break;
            case '-':
                break;
            default:
                *q = *p;
                ++q;
                break;
        }
    }

    memcpy(s, buf, sizeof(char) * 9);

    free(buf);
    return s;
}

int main() {
    int n = 0;
    scanf("%d", &n);

    char **telNumbers = (char **) malloc(sizeof(char *) * n);

    // Input
    for (int i = 0; i < n; ++i) {
        telNumbers[i] = (char *) malloc(sizeof(char *) * MAX_LENGTH);
        scanf("%s", telNumbers[i]);
        toStandardForm(telNumbers[i]);
    }

    // Sort
    qsort(telNumbers, n, sizeof(char *), cmp);

    // Output
    int *con = (int *) (telNumbers[0] + 9);
    *con = 1;
    int dup = 0;

    for (int i = 1; i < n; ++i) {
        if (strcmp(telNumbers[i], telNumbers[i - 1]) == 0) {
            ++(*con);
        } else {
            if (*con > 1) {
                printf("%s %d\n", telNumbers[i - 1], *con);
                dup = 1;
            }

            con = (int *) (telNumbers[i] + 9);
            *con = 1;
        }
    }

    if (*con > 1) {
        printf("%s %d\n", telNumbers[n - 1], *con);
        dup = 1;
    }

    if (!dup) printf("No duplicates.\n");

    // Clean
    for (int i = 1; i < n; ++i) free(telNumbers[i]);
    free(telNumbers);

    return 0;
}
