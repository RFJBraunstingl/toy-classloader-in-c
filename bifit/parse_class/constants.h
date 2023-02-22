#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helpers.h"

typedef struct class_identifier {



} class_identifier_t;

typedef struct {

    // every constant has a type (/tag)
    uint8_t type;

    // for utf8 constants
    const uint8_t *utf8_str;
    int utf8_str_len;

    // for names and descriptions
    int name_index;
    int desc_index;

    // for whole numbers
    long long_value;

    // for floating point
    double double_value;

    // for class refs
    int class_index;
    int name_and_type_index;

    // for method handles
    uint8_t ref_type;
    int ref_index;

} const_pool_entry_t;

int parse_next_constant_pool_entry(int index, const uint8_t *data, const_pool_entry_t *out);

int parse_next_utf8(int index, const uint8_t *data, const_pool_entry_t *out);

int parse_next_integer(int index, const uint8_t *data, const_pool_entry_t *out);

int parse_next_float(int index, const uint8_t *data, const_pool_entry_t *out);

int parse_next_class_ref(int index, const uint8_t *data, const_pool_entry_t *out);

int parse_next_long(int index, const uint8_t *data, const_pool_entry_t *out);

int parse_next_double(int index, const uint8_t *data, const_pool_entry_t *out);

int parse_next_string(int index, const uint8_t *data, const_pool_entry_t *out);

int parse_next_field_ref(int index, const uint8_t *data, const_pool_entry_t *out);

int parse_next_method_ref(int index, const uint8_t *data, const_pool_entry_t *out);

int parse_next_iface_method_ref(int index, const uint8_t *data, const_pool_entry_t *out);

int parse_next_name_and_type(int index, const uint8_t *data, const_pool_entry_t *out);

int parse_next_method_handle(int index, const uint8_t *data, const_pool_entry_t *out);

/**
 * Parse constant pool of given class file
 *
 * @param data an array of bytes which represent the class file
 * @return the index of the first byte which is not part of the constant pool
 */
int parse_constant_pool(const uint8_t data[]) {
    int const_pool_count = parse_integer_u2(8, data);
    LOG_DEBUG("dealing with a constant pool of size %d (-1)\n", const_pool_count);

    int index = 10;
    for (int i = 1; i < const_pool_count; i++) {
        LOG_DEBUG("reading constant pool entry %d\n", i);
        const_pool_entry_t *entry = malloc(sizeof(const_pool_entry_t));
        index = parse_next_constant_pool_entry(index, data, entry);
        LOG_DEBUG("\n");
    }

    return index;
}

int scan_class_identifier(const uint8_t data[], class_identifier_t *out) {
    int given_const_pool_count = parse_integer_u2(8, data);

    int byte_index = 9;
    for (int i = 1; i < given_const_pool_count; i++) {
        uint8_t tag = data[++byte_index];

    }

    return 0;
}

int parse_next_constant_pool_entry(int index, const uint8_t *data, const_pool_entry_t *out) {
    uint8_t tag = data[index++];
    LOG_DEBUG("constant has tag %d ", tag);

    switch (tag) {

        case 1:
            return parse_next_utf8(index, data, out);

        case 3:
            return parse_next_integer(index, data, out);

        case 4:
            return parse_next_float(index, data, out);

        case 5:
            return parse_next_long(index, data, out);

        case 6:
            return parse_next_double(index, data, out);

        case 7:
            return parse_next_class_ref(index, data, out);

        case 8:
            return parse_next_string(index, data, out);

        case 9:
            return parse_next_field_ref(index, data, out);

        case 10:
            return parse_next_method_ref(index, data, out);

        case 11:
            return parse_next_iface_method_ref(index, data, out);

        case 12:
            return parse_next_name_and_type(index, data, out);

        case 15:
            return parse_next_method_handle(index, data, out);

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
int parse_next_utf8(int index, const uint8_t *data, const_pool_entry_t *out) {
    LOG_DEBUG("(UTF-8 constant)\n");
    int length = parse_integer_u2(index, data);
    index += 2;
    LOG_DEBUG("length was %d\n", length);

    out->utf8_str = &data[index];
    out->utf8_str_len = length;

    LOG_DEBUG("attempt to print utf8 as ascii: ");
    for (int i = 0; i < out->utf8_str_len; i++) {
        LOG_DEBUG("%c", out->utf8_str[i]);
    }
    LOG_DEBUG("\n");

    return index + length;
}

/*
CONSTANT_Integer_info {
    u1 tag;
    u4 bytes;
}
 */
int parse_next_integer(int index, const uint8_t *data, const_pool_entry_t *out) {

    LOG_DEBUG("(int)\n");

    uint8_t bytes[4];
    bytes[3] = data[index++];
    bytes[2] = data[index++];
    bytes[1] = data[index++];
    bytes[0] = data[index++];

    out->long_value = *(int *)bytes;
    LOG_DEBUG("integer was %ld\n", out->long_value);

    return index;
}

/*
CONSTANT_Float_info {
    u1 tag;
    u4 bytes;
}
*/
int parse_next_float(int index, const uint8_t *data, const_pool_entry_t *out) {

    LOG_DEBUG("(float)\n");

    uint8_t bytes[4];
    bytes[3] = data[index++];
    bytes[2] = data[index++];
    bytes[1] = data[index++];
    bytes[0] = data[index++];

    out->double_value = *(float *)bytes;
    LOG_DEBUG("float was %f\n", out->double_value);

    return index;
}

/*
CONSTANT_Long_info {
    u1 tag;
    u4 high_bytes;
    u4 low_bytes;
}
*/
int parse_next_long(int index, const uint8_t *data, const_pool_entry_t *out) {

    LOG_DEBUG("(long)\n");

    uint8_t bytes[8];
    bytes[7] = data[index++];
    bytes[6] = data[index++];
    bytes[5] = data[index++];
    bytes[4] = data[index++];
    bytes[3] = data[index++];
    bytes[2] = data[index++];
    bytes[1] = data[index++];
    bytes[0] = data[index++];

    out->long_value = *(long *)bytes;
    LOG_DEBUG("long was %ld\n", out->long_value);

    return index;
}

/*
CONSTANT_Double_info {
    u1 tag;
    u4 high_bytes;
    u4 low_bytes;
}
*/
int parse_next_double(int index, const uint8_t *data, const_pool_entry_t *out) {

    LOG_DEBUG("(double)\n");

    uint8_t bytes[8];
    bytes[7] = data[index++];
    bytes[6] = data[index++];
    bytes[5] = data[index++];
    bytes[4] = data[index++];
    bytes[3] = data[index++];
    bytes[2] = data[index++];
    bytes[1] = data[index++];
    bytes[0] = data[index++];

    out->double_value = *(double *)bytes;
    LOG_DEBUG("double was %f\n", out->double_value);

    return index;
}

/*
CONSTANT_Class_info {
    u1 tag;
    u2 name_index;
}
 */
int parse_next_class_ref(int index, const uint8_t *data, const_pool_entry_t *out) {

    LOG_DEBUG("(class ref)\n");

    out->name_index = parse_integer_u2(index, data);
    LOG_DEBUG("name_index was %d\n", out->name_index);

    return index + 2;
}

/*
CONSTANT_String_info {
    u1 tag;
    u2 string_index;
}
*/
int parse_next_string(int index, const uint8_t *data, const_pool_entry_t *out) {

    LOG_DEBUG("(string)\n");

    out->name_index = parse_integer_u2(index, data);
    LOG_DEBUG("string_index was %d\n", out->name_index);

    return index + 2;
}

/*
CONSTANT_???ref_info {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
}
*/
int parse_next_ref(int index, const uint8_t *data, const_pool_entry_t *out) {
    out->class_index = parse_integer_u2(index, data);
    index += 2;
    LOG_DEBUG("class_index was %d\n", out->class_index);

    out->name_and_type_index = parse_integer_u2(index, data);
    index += 2;
    LOG_DEBUG("name and type index was %d\n", out->name_and_type_index);

    return index;
}

/*
CONSTANT_Fieldref_info {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
}
*/
int parse_next_field_ref(int index, const uint8_t *data, const_pool_entry_t *out) {
    LOG_DEBUG("(field ref)\n");
    return parse_next_ref(index, data, out);
}

/*
CONSTANT_Methodref_info {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
}
*/
int parse_next_method_ref(int index, const uint8_t *data, const_pool_entry_t *out) {
    LOG_DEBUG("(method ref)\n");
    return parse_next_ref(index, data, out);
}

/*
CONSTANT_InterfaceMethodref_info {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
}
*/
int parse_next_iface_method_ref(int index, const uint8_t *data, const_pool_entry_t *out) {
    LOG_DEBUG("(interface method ref)\n");
    return parse_next_ref(index, data, out);
}

/*
CONSTANT_NameAndType_info {
    u1 tag;
    u2 name_index;
    u2 descriptor_index;
}
*/
int parse_next_name_and_type(int index, const uint8_t *data, const_pool_entry_t *out) {

    LOG_DEBUG("(name and type constant)\n");

    out->name_index = parse_integer_u2(index, data);
    index += 2;
    LOG_DEBUG("name_index was %d\n", out->name_index);

    out->desc_index = parse_integer_u2(index, data);
    index += 2;
    LOG_DEBUG("desc_index was %d\n", out->desc_index);

    return index;
}

/*
CONSTANT_MethodHandle_info {
    u1 tag;
    u1 reference_kind;
    u2 reference_index;
}
*/
int parse_next_method_handle(int index, const uint8_t *data, const_pool_entry_t *out) {

    LOG_DEBUG("(method handle)\n");

    out->ref_type = data[index++];
    LOG_DEBUG("reference_kind was %d\n", out->ref_type);

    out->ref_index = parse_integer_u2(index, data);
    LOG_DEBUG("reference_index was %d\n", out->ref_index);

    return index + 2;
}