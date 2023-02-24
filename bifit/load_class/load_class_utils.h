#ifndef LOAD_CLASS_UTILS_H_
#define LOAD_CLASS_UTILS_H_

#include <stdlib.h>

int parse_integer_u2(unsigned int index, const uint8_t data[]) {
    int result = data[index];
    result  = result << 8;

    result += data[index + 1];

    return result;
}

int parse_integer_u4(unsigned int index, const uint8_t data[]) {
    int result = data[index++];
    result = result << 8;

    result += data[index++];
    result = result << 8;

    result += data[index++];
    result = result << 8;

    result += data[index];

    return result;
}

void load_identifier_by_name_index(int name_index, bifit_constant_pool_entry_t entries[], bifit_identifier_t *out) {
    bifit_constant_pool_entry_t identifier_entry = entries[name_index];

}

#endif