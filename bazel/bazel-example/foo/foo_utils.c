#include "foo/foo_utils.h"

#include <time.h>
#include <stdio.h>

void foo_print_time(void) {
    printf("%lld\n", (long long) time(NULL));
}
