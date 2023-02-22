#include <stdlib.h>

#include "helpers.h"

int parse_fields(int index, const uint8_t data[]) {
    LOG_DEBUG("parse_fields\n");
    int field_count = parse_integer_u2(index, data);
    index += 2;
    LOG_DEBUG("field_count: %d\n", field_count);

    if (field_count > 0) {
        LOG_DEBUG("ERROR: field parsing not implemented!");
        exit(1);
    }

    return index;
}