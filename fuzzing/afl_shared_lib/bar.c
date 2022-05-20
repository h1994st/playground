#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#include "foo.h"
#include "foo2.h"

int main() {
    char str[100];
    read(0, str, 100);

    wrong_print(str);
    wrong_print2(str);

    return 0;
}
