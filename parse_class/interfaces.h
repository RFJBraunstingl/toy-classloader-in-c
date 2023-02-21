#include <stdlib.h>

#include "helpers.h"

int parse_interfaces(int index, const uint8_t data[]) {
    LOG_DEBUG("parse_interfaces\n");
    int interface_count = parse_integer_u2(index, data);
    index += 2;
    LOG_DEBUG("interface_count: %d\n", interface_count);

    if (interface_count > 0) {
        LOG_DEBUG("ERROR: interface parsing not implemented!");
        exit(1);
    }

    return index;
}