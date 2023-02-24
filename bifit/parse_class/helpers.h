#ifndef CLASS_PARSE_HELPERS_H__
#define CLASS_PARSE_HELPERS_H__

#include <stdlib.h>
#include <stdio.h>

/*
 * u2 access_flags
 */
int parse_access_flags(int index, const uint8_t data[]) {

    LOG_DEBUG("parsing access flags\n");
    uint8_t access_flags_msb = data[index++];
    uint8_t access_flags_lsb = data[index++];

    if (0x80 & access_flags_msb) {
        LOG_DEBUG("access_flags: ACC_MODULE\n");
    }
    if (0x40 & access_flags_msb) {
        LOG_DEBUG("access_flags: ACC_ENUM\n");
    }
    if (0x20 & access_flags_msb) {
        LOG_DEBUG("access_flags: ACC_ANNOTATION\n");
    }
    if (0x10 & access_flags_msb) {
        LOG_DEBUG("access_flags: ACC_SYNTHETIC\n");
    }
    if (0x04 & access_flags_msb) {
        LOG_DEBUG("access_flags: ACC_ABSTRACT\n");
    }
    if (0x02 & access_flags_msb) {
        LOG_DEBUG("access_flags: ACC_INTERFACE\n");
    }
    if (0x20 & access_flags_lsb) {
        LOG_DEBUG("access_flags: ACC_SUPER\n");
    }
    if (0x10 & access_flags_lsb) {
        LOG_DEBUG("access_flags: ACC_FINAL\n");
    }
    if (0x01 & access_flags_lsb) {
        LOG_DEBUG("access_flags: ACC_PUBLIC\n");
    }

    LOG_DEBUG("\n");
    return index;
}

/*
 * u2 this_class
 */
int parse_this_class(int index, const uint8_t data[]) {
    int class_index = parse_integer_u2(index, data);
    LOG_DEBUG("this_class index: %d\n", class_index);

    return index + 2;
}

int read_this_class_index(int index, const uint8_t data[]) {
    int this_class_index = parse_integer_u2(index, data);
    LOG_DEBUG("this_class_index: %d\n", this_class_index);

    return this_class_index;
}

/*
 * u2 super_class
 */
int parse_super_class(int index, const uint8_t data[]) {
    int class_index = parse_integer_u2(index, data);
    LOG_DEBUG("super_class index: %d\n", class_index);

    return index + 2;
}

#endif