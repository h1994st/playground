#include "foo_utils.h"
#include <stdio.h>
#include <time.h>

void foo_print_time(void) { printf("%lld\n", (long long)time(NULL)); }
