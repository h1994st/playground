#include <stdio.h>

int p, e, i, d;
int j;
int ans;
int lcm = 21252;

/**
 * @input: p, e, i, d
 * (ans + d) mod 23 = p
 * (ans + d) mod 28 = e
 * (ans + d) mod 33 = i
 *
 * 中国剩余定理
 * 模逆元
 * 扩展欧几里得算法
 * 辗转相除法
 * 更相减损法
 * 大衍求一术
 *
 * @output ans
 */
int main() {
    scanf("%d %d %d %d", &p, &e, &i, &d);

    while (p != -1 && e != -1 && i != -1 && d != -1) {
        ++j;

        ans = (5544 * p + 14421 * e + 1288 * i - d + lcm) % lcm;
        if (ans == 0) ans = lcm;

        // while (ans <= 0) ans += 21252;
        // while (ans > 21252) ans -= 21252;

        printf("Case %d: the next triple peak occurs in %d days.\n", j, ans);

        scanf("%d %d %d %d", &p, &e, &i, &d);
    }

    return 0;
}
