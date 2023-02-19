#include <stdlib.h>

#include "helpers.h"

int parse_methods(int index, const uint8_t data[]) {
    printf("parse_methods\n");
    int method_count = parse_integer_u2(index, data);
    index += 2;
    printf("method_count: %d\n", method_count);

    return index;
}