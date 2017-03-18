#include <stdio.h>
#include <stdlib.h>

int n, m;

typedef struct {
    char seq[50];
    int unorderness;
} DNA;

DNA input[100];

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; ++i) {
        scanf("%s", input[i].seq);

        for (int j = 0; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                if (input[i].seq[j] > input[i].seq[k]) {
                    ++input[i].unorderness;
                }
            }
        }
    }

    // Insertion sort
    DNA temp;
    for (int i = 1; i < m; ++i) {
        temp = input[i];
        int j = i - 1;
        while (j >= 0 && input[j].unorderness > temp.unorderness) {
            input[j + 1] = input[j];
            --j;
        }
        input[j + 1] = temp;
    }

    for (int i = 0; i < m; ++i) {
        printf("%s\n", input[i].seq);
    }

    return 0;
}
