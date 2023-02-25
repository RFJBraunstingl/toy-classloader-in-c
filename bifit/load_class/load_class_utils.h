#ifndef LOAD_CLASS_UTILS_H_
#define LOAD_CLASS_UTILS_H_

#include <stdlib.h>

unsigned int parse_integer_u2(unsigned int index, const uint8_t data[]) {
    unsigned int result = data[index];
    result  = result << 8;

    result += data[index + 1];

    return result;
}

unsigned int parse_integer_u4(unsigned int index, const uint8_t data[]) {
    unsigned int result = data[index++];
    result = result << 8;

    result += data[index++];
    result = result << 8;

    result += data[index++];
    result = result << 8;

    result += data[index];

    return result;
}

void load_identifier_by_name_index(unsigned int name_index, bifit_constant_pool_entry_t entries[], bifit_identifier_t *out) {
    bifit_constant_pool_entry_t identifier_entry = entries[name_index];
    // TODO: check if actually utf8 constant?
    out->class_identifier = identifier_entry.utf8_str;
    out->class_identifier_length = identifier_entry.utf8_str_len;
}

/*
attribute_info {
    u2 attribute_name_index;
    u4 attribute_length;
    u1 info[attribute_length];
}
*/
unsigned int load_attribute(unsigned int index, const uint8_t *data, bifit_constant_pool_entry_t entries[], bifit_attribute_t *out) {
    unsigned int name_index = parse_integer_u2(index, data);
    load_identifier_by_name_index(name_index, entries, &out->name);
    index += 2;

    out->length_in_bytes = parse_integer_u4(index, data);
    index += 4;

    out->data = &data[index];

    return index;
}

#endif