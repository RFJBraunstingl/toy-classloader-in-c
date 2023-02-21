#ifndef CLASS_PARSE_HELPERS_H__
#define CLASS_PARSE_HELPERS_H__

#include <stdlib.h>
#include <stdio.h>

int parse_integer_u2(int index, const uint8_t data[]) {
    uint8_t msb = data[index];
    uint8_t lsb = data[index + 1];

    return msb * 16 + lsb;
}

/*
 * u2 access_flags
 */
int parse_access_flags(int index, const uint8_t data[]) {

    printf("parsing access flags\n");
    uint8_t access_flags_msb = data[index++];
    uint8_t access_flags_lsb = data[index++];

    if (0x80 & access_flags_msb) {
        printf("access_flags: ACC_MODULE\n");
    }
    if (0x40 & access_flags_msb) {
        printf("access_flags: ACC_ENUM\n");
    }
    if (0x20 & access_flags_msb) {
        printf("access_flags: ACC_ANNOTATION\n");
    }
    if (0x10 & access_flags_msb) {
        printf("access_flags: ACC_SYNTHETIC\n");
    }
    if (0x04 & access_flags_msb) {
        printf("access_flags: ACC_ABSTRACT\n");
    }
    if (0x02 & access_flags_msb) {
        printf("access_flags: ACC_INTERFACE\n");
    }
    if (0x20 & access_flags_lsb) {
        printf("access_flags: ACC_SUPER\n");
    }
    if (0x10 & access_flags_lsb) {
        printf("access_flags: ACC_FINAL\n");
    }
    if (0x01 & access_flags_lsb) {
        printf("access_flags: ACC_PUBLIC\n");
    }

    printf("\n");
    return index;
}

/*
 * u2 this_class
 */
int parse_this_class(int index, const uint8_t data[]) {
    int class_index = parse_integer_u2(index, data);
    printf("this_class index: %d\n", class_index);

    return index + 2;
}

/*
 * u2 super_class
 */
int parse_super_class(int index, const uint8_t data[]) {
    int class_index = parse_integer_u2(index, data);
    printf("super_class index: %d\n", class_index);

    return index + 2;
}

#endif