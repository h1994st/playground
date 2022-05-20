#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#include "foo2.h"

void wrong_print2(char *input) {
    if (input[1] == 'O') {
        if (input[5] == 'Y') {
            abort();
        }
    }
}
