#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "HelloWorld_class.h"
#include "Greeter_class.h"

void parse_class_header(uint8_t data[]);

void parse_constant_pool(uint8_t data[]);

int parse_next_constant_pool_entry(int index, const uint8_t *data);

int parse_next_method_ref(int index, const uint8_t *data);

int parse_next_utf8(int index, const uint8_t *data);

int parse_next_class_ref(int index, const uint8_t *data);

int parse_next_integer(int index, const uint8_t *data);

void guess_java_version(char *major_version, char *target) {
    int version_number = (int) strtol(major_version, NULL, 16);
    printf("major version number is %d\n", version_number);

    int java_version = version_number - 44;

    sprintf(target, "Java %d", java_version);
}

int main() {
    printf("Hello, World!\n");

    // load class
    printf("loading class Hello World\n");
    parse_class_header(HelloWorld_class_data);
    parse_constant_pool(HelloWorld_class_data);

    return 0;
}

/**
 * Read the first 8 bytes from the class file
 * which provide information about the java version
 *
 * @param data
 */
void parse_class_header(uint8_t data[]) {
    printf("magic number is '%x%x %x%x'\n",
           data[0],
           data[1],
           data[2],
           data[3]
    );

    printf("minor version: %x%x\n", data[4], data[5]);
    char major_version[4];
    sprintf(major_version, "%x%x", data[6], data[7]);
    printf("major version: %s\n", major_version);

    char java_version_description[10];
    guess_java_version(major_version, java_version_description);
    printf("guessing java version: %s\n", java_version_description);
}

void parse_constant_pool(uint8_t data[]) {
    int const_pool_count = data[8] * 16 + data[9];
    printf("dealing with a constant pool of size (%d-1)\n", const_pool_count);

    int index = 9;
    for (int i = 1; i < 5; i++) {
        printf("\nreading constant pool entry %d\n", i);
        index = parse_next_constant_pool_entry(index, data);
    }
}

int parse_next_constant_pool_entry(int index, const uint8_t *data) {
    uint8_t tag = data[++index];
    printf("constant has tag %d\n", tag);

    switch (tag) {

        case 1:
            return parse_next_utf8(index, data);

        case 3:
            return parse_next_integer(index, data);

        case 7:
            return parse_next_class_ref(index, data);

        case 10:
            return parse_next_method_ref(index, data);

        default:
            return index;
    }
}

/*
CONSTANT_Utf8_info {
    u1 tag;
    u2 length;
    u1 bytes[length];
}
*/
int parse_next_utf8(int index, const uint8_t *data)
{
    uint8_t length_msb = data[++index];
    uint8_t length_lsb = data[++index];
    int length = length_msb * 16 + length_lsb;
    printf("length was %d\n", length);

    uint8_t utf8_const[length];
    memcpy(&utf8_const, &data[index], length);
    printf("attempt to print utf8 as ascii: %s\n", utf8_const);

    return index + length;
}

/*
CONSTANT_Integer_info {
    u1 tag;
    u4 bytes;
}
 */
int parse_next_integer(int index, const uint8_t *data) {

    uint8_t bytes[4];
    bytes[3] = data[++index];
    bytes[2] = data[++index];
    bytes[1] = data[++index];
    bytes[0] = data[++index];

    int result = *(int *)bytes;
    printf("integer was %d\n", result);

    return index;
}

/*
CONSTANT_Class_info {
    u1 tag;
    u2 name_index;
}
 */
int parse_next_class_ref(int index, const uint8_t *data) {

    uint8_t name_index_msb = data[++index];
    uint8_t name_index_lsb = data[++index];
    int name_index = name_index_msb * 16 + name_index_lsb;
    printf("name_index was %d\n", name_index);

    return index;
}

/*
CONSTANT_Methodref_info {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
}
*/
int parse_next_method_ref(int index, const uint8_t *data) {

    uint8_t class_index_msb = data[++index];
    uint8_t class_index_lsb = data[++index];
    int class_index = class_index_msb * 16 + class_index_lsb;
    printf("class_index was %d\n", class_index);

    uint8_t name_and_type_index_msb = data[++index];
    uint8_t name_and_type_index_lsb = data[++index];
    int name_and_type_index = name_and_type_index_msb * 16 + name_and_type_index_lsb;
    printf("name and type index was %d\n", name_and_type_index);

    return index;
}
