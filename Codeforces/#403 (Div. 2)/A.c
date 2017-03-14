#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n = 0, sock = 0, cur = 0, maxSock = 0;
    scanf("%d", &n);

    int *temp = (int *) malloc(sizeof(int) * n);
    memset(temp, 0, sizeof(int) * n);

    for (int i = 0; i < 2 * n; ++i) {
        scanf("%d", &sock);
        --sock;
        if (!temp[sock]) {
            temp[sock] = 1;
            ++cur;
        } else {
            temp[sock] = 0;
            --cur;
        }
        maxSock = cur > maxSock ? cur : maxSock;
        // printf("sock: %d, cur: %d, max: %d\n", sock, cur, maxSock);
    }

    printf("%d\n", maxSock);
    free(temp);

    return 0;
}
