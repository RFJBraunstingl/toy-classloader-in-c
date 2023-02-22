#include <stdlib.h>

#include "helpers.h"

int parse_attributes(int index, const uint8_t data[]) {
    LOG_DEBUG("parse_attributes\n");
    int attribute_count = parse_integer_u2(index, data);
    index += 2;
    LOG_DEBUG("attribute_count: %d\n", attribute_count);

    return index;
}