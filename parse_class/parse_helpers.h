#include <stdlib.h>
#include <stdio.h>

int parse_u2(int index, const uint8_t data[]);
int parse_this_class(int index, uint8_t data[]);
int parse_super_class(int index, uint8_t data[]);

int parse_integer_u2(int index, const uint8_t data[]) {
    uint8_t msb = data[index];
    uint8_t lsb = data[index + 1];

    return msb * 16 + lsb;
}

/*
 * u2 this_class
 */
int parse_this_class(int index, uint8_t data[]) {
    int class_index = parse_integer_u2(index, data);
    printf("this_class index: %d\n", class_index);

    return index + 2;
}

/*
 * u2 super_class
 */
int parse_super_class(int index, uint8_t data[]) {
    int class_index = parse_integer_u2(index, data);
    printf("super_class index: %d\n", class_index);

    return index + 2;
}