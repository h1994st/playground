#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strnumStrip(char *s) {
    size_t len = strlen(s);
    if (len == 0) return s;

    char *p = s, *end = s + len - 1, *ret = NULL;

    // Removing leading zeros
    for (; *p != '\0' && *p == '0'; ++p) ;

    // Removing following zeros
    for (; end >= p && *end == '0'; --end) ;

    // Dot
    if (*end != '.') ++end;
    *end = '\0';

    ret = (char *) malloc(sizeof(char) * (end - p + 1));
    strcpy(ret, p);

    return ret;
}

char *strnumMultiply(char *s1, char *s2) {
    char *ret = NULL;
    char *result = NULL;
    int *intRet = NULL;
    long intLen = 0;

    int *sInt1 = NULL, *sInt2 = NULL;
    long sIntLen1 = 0, sIntLen2 = 0;

    long dotIndex1 = -1, dotIndex2 = -1;
    long dotLen = 0;

    char *p1 = NULL;
    int *pInt1 = NULL, *pInt2 = NULL, *pInt3 = NULL;

    p1 = strstr(s1, ".");
    if (p1) dotIndex1 = p1 - s1;

    p1 = strstr(s2, ".");
    if (p1) dotIndex2 = p1 - s2;

    sIntLen1 = strlen(s1) - (dotIndex1 == -1 ? 0 : 1);
    sIntLen2 = strlen(s2) - (dotIndex2 == -1 ? 0 : 1);

    dotLen = (dotIndex1 == -1 ? 0 : (sIntLen1 - dotIndex1));
    dotLen += (dotIndex2 == -1 ? 0 : (sIntLen2 - dotIndex2));

    sInt1 = (int *) malloc(sizeof(int) * sIntLen1);
    sInt2 = (int *) malloc(sizeof(int) * sIntLen2);

    // init
    for (p1 = s1, pInt1 = sInt1; *p1 != '\0'; ++p1) {
        if (*p1 != '.') {
            *pInt1 = *p1 - '0';
            ++pInt1;
        }
    }

    for (p1 = s2, pInt1 = sInt2; *p1 != '\0'; ++p1) {
        if (*p1 != '.') {
            *pInt1 = *p1 - '0';
            ++pInt1;
        }
    }

    intLen = sIntLen1 + sIntLen2;
    intRet = calloc(intLen, sizeof(int));
    int round = 0, temp = 0;
    for (pInt2 = sInt2 + sIntLen2 - 1, round = 0; pInt2 >= sInt2; --pInt2, ++round) {
        if (*pInt2 == 0) continue;

        pInt3 = intRet + intLen - 1 - round;
        for (pInt1 = sInt1 + sIntLen1 - 1; pInt1 - sInt1 >= 0; --pInt1) {

            *pInt3 += ((*pInt1) * (*pInt2));

            if (*pInt3 >= 10) {
                temp = *pInt3;
                *pInt3 = temp % 10;
                *(pInt3 - 1) += (temp / 10);
            }

            --pInt3;
        }
    }

    result = calloc(intLen + 3, sizeof(char));
    for (p1 = result + intLen + 1, pInt1 = intRet + intLen - 1; pInt1 >= intRet; --p1, --pInt1) {
        if (p1 - result == intLen - dotLen + 1) {
            // Add dot
            *p1 = '.';
            ++pInt1;
        } else {
            *p1 = *pInt1 + '0';
        }
    }

    if (p1 - result == intLen - dotLen + 1) {
        *p1 = '.';
        --p1;
    }

    for (; p1 >= result; --p1) *p1 = '0';

    ret = strnumStrip(result);

    free(sInt1);
    free(sInt2);
    free(intRet);
    free(result);

    return ret;
}

char *strnumPow(char *base, int exp) {
    if (exp == 0) return "1";
    if (exp == 1) return base;
    if (strlen(base) == 0 || strcmp(base, "0") == 0) return "0";

    char *ret = NULL;
    ret = strnumPow(base, exp / 2);
    ret = strnumMultiply(ret, ret);
    if (exp % 2 != 0) ret = strnumMultiply(ret, base);

    return ret;
}

/**
 * @url http://poj.org/problem?id=1001
 */
int main() {
    char r[7];
    int n;

    while (scanf("%s %d", r, &n) != EOF) {
        char *ret = strnumPow(strnumStrip(r), n);
        printf("%s\n", ret);
        free(ret);
    }

    return 0;
}
