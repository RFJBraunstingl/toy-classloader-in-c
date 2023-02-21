#include <stdlib.h>

#include "helpers.h"

int parse_fields(int index, const uint8_t data[]) {
    printf("parse_fields\n");
    int field_count = parse_integer_u2(index, data);
    index += 2;
    printf("field_count: %d\n", field_count);

    if (field_count > 0) {
        printf("ERROR: field parsing not implemented!");
        exit(1);
    }

    return index;
}