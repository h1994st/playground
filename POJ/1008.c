#include <stdio.h>
#include <stdlib.h>

int n;
int day, month, year, total;
char temp[10];

// Tzolkin
// imix, ik, akbal, kan, chicchan
// cimi, manik, lamat, muluk, ok
// chuen, eb, ben, ix, mem
// cib, caban, eznab, canac, ahau
char tzolkinDays[20][10] = {
    "imix", "ik", "akbal", "kan", "chicchan",
    "cimi", "manik", "lamat", "muluk", "ok",
    "chuen", "eb", "ben", "ix", "mem",
    "cib", "caban", "eznab", "canac", "ahau"
};

// Haab
// pop, no, zip, zotz, tzec, xul
// yoxkin, mol, chen, yax, zac, ceh
// mac, kankin, muan, pax, koyab, cumhu
// uayet
int haabMonthStrToInt(const char *p) {
    switch (p[0]) {
        case 'p':
            switch (p[1]) {
                case 'o':
                    // pop
                    return 0;
                    break;
                case 'a':
                    // pax
                    return 15;
                    break;
            }
            break;
        case 'n':
            // no
            return 1;
            break;
        case 'z':
            switch (p[1]) {
                case 'i':
                    // zip
                    return 2;
                    break;
                case 'o':
                    // zotz
                    return 3;
                    break;
                case 'a':
                    // zac
                    return 10;
                    break;
            }
            break;
        case 't':
            // tzec
            return 4;
            break;
        case 'x':
            // xul
            return 5;
            break;
        case 'y':
            switch (p[1]) {
                case 'o':
                    // yoxkin
                    return 6;
                    break;
                case 'a':
                    // yax
                    return 9;
                    break;
            }
            break;
        case 'm':
            switch (p[1]) {
                case 'o':
                    // mol
                    return 7;
                    break;
                case 'a':
                    // mac
                    return 12;
                    break;
                case 'u':
                    // muan
                    return 14;
                    break;
            }
            break;
        case 'c':
            switch (p[1]) {
                case 'h':
                    // chen
                    return 8;
                    break;
                case 'e':
                    // ceh
                    return 11;
                    break;
                case 'u':
                    // cumhu
                    return 17;
                    break;
            }
            break;
        case 'k':
            switch (p[1]) {
                case 'a':
                    // kankin
                    return 13;
                    break;
                case 'o':
                    // koyab
                    return 16;
                    break;
            }
            break;
        case 'u':
            // uayet
            return 18;
            break;
        default:
            return -1;
            break;
    }
    return -1;
}

int main() {
    scanf("%d", &n);
    printf("%d\n", n);

    while (n--) {
        total = 0;
        scanf("%d. %s %d", &day, temp, &year);
        month = haabMonthStrToInt(temp);

        total = year * 365 + month * 20 + day;

        year = total / 260;
        month = total % 20;
        day = total % 13 + 1;

        printf("%d %s %d\n", day, tzolkinDays[month], year);
    }

    return 0;
}
