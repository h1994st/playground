#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.141592653589
#endif

int n;
double x, y;
int ans;

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%lf %lf", &x, &y);

        ans = (int) ceil(M_PI * (x * x + y * y) / 100.0f);

        printf("Property %d: This property will begin eroding in year %d.\n", i + 1, ans);
    }

    printf("END OF OUTPUT.\n");

    return 0;
}
