#include <stdio.h>

#include "./parse_class/class_header.h"
#include "./parse_class/constant_pool.h"
#include "./parse_class/parse_helpers.h"

#include "HelloWorld_class.h"
#include "Greeter_class.h"

int parse_access_flags(int index, const uint8_t data[]);

int parse_this_class(int index, uint8_t data[]);

int parse_super_class(int index, uint8_t data[]);

int main() {
    printf("Hello, World!\n");

    // load class
    printf("loading class Hello World\n");
    parse_class_header(HelloWorld_class_data);
    int index = parse_constant_pool(HelloWorld_class_data);

    index = parse_access_flags(index, HelloWorld_class_data);

    index = parse_this_class(index, HelloWorld_class_data);
    index = parse_super_class(index, HelloWorld_class_data);

    return 0;
}

/*
 * u2 access_flags
 */
int parse_access_flags(int index, const uint8_t data[]) {

    printf("\nparsing access flags\n");
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

