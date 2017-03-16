#include <stdio.h>

int main() {
    double balance, result = 0.0f;
    for (int i = 0; i < 12; ++i) {
        scanf("%lf", &balance);
        result += balance;
    }

    // %lf will lead to wrong answer, strange
    printf("$%.2f\n", result / 12);

    return 0;
}
