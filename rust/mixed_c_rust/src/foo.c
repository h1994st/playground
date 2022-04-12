#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

extern uint8_t objects[];
extern size_t objects_size;

void baz() {
    printf("haha\n");
    printf("objects=%p\n", objects);
    printf("objects_size=%zu\n", objects_size);

    for (size_t i = 0; i < objects_size; ++i) {
        objects[i] = (uint8_t) i;
    }
}
