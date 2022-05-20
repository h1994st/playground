#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#include "foo.h"

void wrong_print(char *input) {
    if (input[1] == 'E') {
        if (input[2] == 'F') {
            abort();
        }
    }
}
