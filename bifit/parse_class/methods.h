#include <stdlib.h>

#include "helpers.h"

int parse_next_method_entry(int index, const uint8_t *data);

int parse_method_access_flags(int index, const uint8_t *data);

int parse_method_name_index(int index, const uint8_t *data);

int parse_method_desc_index(int index, const uint8_t *data);

int parse_method_attributes(int index, const uint8_t *data);

int parse_next_method_attribute(int index, const uint8_t *data);

/* main */
int parse_methods(int index, const uint8_t data[]) {
    LOG_DEBUG("parse_methods\n");
    int method_count = parse_integer_u2(index, data);
    index += 2;
    LOG_DEBUG("method_count: %d\n", method_count);

    for (int i = 1; i <= method_count; i++) {
        LOG_DEBUG("\nreading method entry %d\n", i);
        index = parse_next_method_entry(index, data);
    }

    return index;
}

/*
method_info {
    u2             access_flags;
    u2             name_index;
    u2             descriptor_index;
    u2             attributes_count;
    attribute_info attributes[attributes_count];
}
*/
int parse_next_method_entry(int index, const uint8_t *data) {
    index = parse_method_access_flags(index, data);
    index = parse_method_name_index(index, data);
    index = parse_method_desc_index(index, data);
    index = parse_method_attributes(index, data);
    return index;
}

// u2 access_flags
int parse_method_access_flags(int index, const uint8_t *data) {
    uint8_t access_flags_msb = data[index++];
    uint8_t access_flags_lsb = data[index++];

    if (0x10 & access_flags_msb) {
        LOG_DEBUG("access_flags: ACC_SYNTHETIC\n");
    }
    if (0x08 & access_flags_msb) {
        LOG_DEBUG("access_flags: ACC_STRICT\n");
    }
    if (0x04 & access_flags_msb) {
        LOG_DEBUG("access_flags: ACC_ABSTRACT\n");
    }
    if (0x01 & access_flags_msb) {
        LOG_DEBUG("access_flags: ACC_NATIVE\n");
    }
    if (0x80 & access_flags_lsb) {
        LOG_DEBUG("access_flags: ACC_VARARGS\n");
    }
    if (0x40 & access_flags_lsb) {
        LOG_DEBUG("access_flags: ACC_BRIDGE\n");
    }
    if (0x20 & access_flags_lsb) {
        LOG_DEBUG("access_flags: ACC_SYNCHRONIZED\n");
    }
    if (0x10 & access_flags_lsb) {
        LOG_DEBUG("access_flags: ACC_FINAL\n");
    }
    if (0x08 & access_flags_lsb) {
        LOG_DEBUG("access_flags: ACC_STATIC\n");
    }
    if (0x04 & access_flags_lsb) {
        LOG_DEBUG("access_flags: ACC_PROTECTED\n");
    }
    if (0x02 & access_flags_lsb) {
        LOG_DEBUG("access_flags: ACC_PRIVATE\n");
    }
    if (0x01 & access_flags_lsb) {
        LOG_DEBUG("access_flags: ACC_PUBLIC\n");
    }

    return index;
}

int parse_method_name_index(int index, const uint8_t *data) {

    int name_index = parse_integer_u2(index, data);
    LOG_DEBUG("method name_index: %d\n", name_index);

    return index + 2;
}

int parse_method_desc_index(int index, const uint8_t *data) {

    int desc_index = parse_integer_u2(index, data);
    LOG_DEBUG("method desc_index: %d\n", desc_index);

    return index + 2;
}

int parse_method_attributes(int index, const uint8_t *data) {
    LOG_DEBUG("parse_method_attributes\n");
    int attr_count = parse_integer_u2(index, data);
    LOG_DEBUG("attribute count is %d\n", attr_count);
    index += 2;

    for (int i = 1; i <= attr_count; i++) {
        LOG_DEBUG("reading attribute %d\n", i);
        index = parse_next_method_attribute(index, data);
    }

    return index;
}

/*
attribute_info {
    u2 attribute_name_index;
    u4 attribute_length;
    u1 info[attribute_length];
}
*/
int parse_next_method_attribute(int index, const uint8_t *data) {

    int name_index = parse_integer_u2(index, data);
    LOG_DEBUG("name_index for attribute: %d\n", name_index);
    index += 2;

    int attribute_length = parse_integer_u4(index, data);
    LOG_DEBUG("attribute_length was %d\n", attribute_length);
    index += 4;

    // uint8_t info[attribute_length];
    // memcpy(&info, &data[index+1], attribute_length);
    // LOG_DEBUG("value:\n");
    // for (int i = 0; i < attribute_length; i++) {
    //     LOG_DEBUG("%02x\n", data[index + i]);
    // }

    return index + attribute_length;
}
