#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
char haabMonths[19][10]={
    "pop","no", "zip", "zotz", "tzec", "xul",
    "yoxkin", "mol", "chen", "yax", "zac", "ceh",
    "mac", "kankin", "muan", "pax", "koyab", "cumhu",
    "uayet"
};

int main() {
    scanf("%d", &n);
    printf("%d\n", n);

    while (n--) {
        scanf("%d. %s %d", &day, temp, &year);

        for (month = 0; month < 19; ++month) {
            if (strcmp(temp, haabMonths[month]) == 0) break;
        }

        total = year * 365 + month * 20 + day;

        printf("%d %s %d\n", total % 13 + 1, tzolkinDays[total % 20], total / 260);
    }

    return 0;
}
