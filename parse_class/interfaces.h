#include <stdlib.h>

#include "parse_helpers.h"

int parse_interfaces(int index, const uint8_t data[]) {
    printf("parse_interfaces\n");
    int interface_count = parse_integer_u2(index, data);
    index += 2;
    printf("interface_count: %d\n", interface_count);

    if (interface_count > 0) {
        printf("ERROR: interface parsing not implemented!");
        exit(1);
    }

    return index;
}