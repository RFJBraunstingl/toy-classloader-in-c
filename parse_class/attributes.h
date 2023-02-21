#include <stdlib.h>

#include "helpers.h"

int parse_attributes(int index, const uint8_t data[]) {
    printf("parse_attributes\n");
    int attribute_count = parse_integer_u2(index, data);
    index += 2;
    printf("attribute_count: %d\n", attribute_count);

    return index;
}