#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int parse_next_constant_pool_entry(int index, const uint8_t *data);

int parse_next_method_ref(int index, const uint8_t *data);

int parse_next_utf8(int index, const uint8_t *data);

int parse_next_integer(int index, const uint8_t *data);

int parse_next_float(int index, const uint8_t *data);

int parse_next_class_ref(int index, const uint8_t *data);

int parse_next_long(int index, const uint8_t *data);

int parse_next_double(int index, const uint8_t *data);

int parse_next_string(int index, const uint8_t *data);

int parse_next_field_ref(int index, const uint8_t *data);

int parse_next_iface_method_ref(int index, const uint8_t *data);

int parse_next_name_and_type(int index, const uint8_t *data);

int parse_next_method_handle(int index, const uint8_t *data);

/**
 * Parse constant pool of given class file
 *
 * @param data an array of bytes which represent the class file
 * @return the index of the first byte which is not part of the constant pool
 */
int parse_constant_pool(const uint8_t data[]) {
    int const_pool_count = data[8] * 16 + data[9];
    LOG_DEBUG("dealing with a constant pool of size %d (-1)\n", const_pool_count);

    int index = 9;
    for (int i = 1; i < const_pool_count; i++) {
        LOG_DEBUG("reading constant pool entry %d\n", i);
        index = parse_next_constant_pool_entry(index, data);
        LOG_DEBUG("\n");
    }

    return index + 1;
}

int parse_next_constant_pool_entry(int index, const uint8_t *data) {
    uint8_t tag = data[++index];
    LOG_DEBUG("constant has tag %d ", tag);

    switch (tag) {

        case 1:
            return parse_next_utf8(index, data);

        case 3:
            return parse_next_integer(index, data);

        case 4:
            return parse_next_float(index, data);

        case 5:
            return parse_next_long(index, data);

        case 6:
            return parse_next_double(index, data);

        case 7:
            return parse_next_class_ref(index, data);

        case 8:
            return parse_next_string(index, data);

        case 9:
            return parse_next_field_ref(index, data);

        case 10:
            return parse_next_method_ref(index, data);

        case 11:
            return parse_next_iface_method_ref(index, data);

        case 12:
            return parse_next_name_and_type(index, data);

        case 15:
            return parse_next_method_handle(index, data);

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
int parse_next_utf8(int index, const uint8_t *data) {
    LOG_DEBUG("(UTF-8 constant)\n");
    uint8_t length_msb = data[++index];
    uint8_t length_lsb = data[++index];
    int length = length_msb * 16 + length_lsb;
    LOG_DEBUG("length was %d\n", length);

    uint8_t utf8_const[length + 1];
    memcpy(&utf8_const, &data[index+1], length);
    utf8_const[length] = '\0';
    LOG_DEBUG("attempt to print utf8 as ascii: %s\n", utf8_const);

    return index + length;
}

/*
CONSTANT_Integer_info {
    u1 tag;
    u4 bytes;
}
 */
int parse_next_integer(int index, const uint8_t *data) {

    LOG_DEBUG("(int)\n");

    uint8_t bytes[4];
    bytes[3] = data[++index];
    bytes[2] = data[++index];
    bytes[1] = data[++index];
    bytes[0] = data[++index];

    int result = *(int *)bytes;
    LOG_DEBUG("integer was %d\n", result);

    return index;
}

/*
CONSTANT_Float_info {
    u1 tag;
    u4 bytes;
}
*/
int parse_next_float(int index, const uint8_t *data) {

    LOG_DEBUG("(float)\n");

    uint8_t bytes[4];
    bytes[3] = data[++index];
    bytes[2] = data[++index];
    bytes[1] = data[++index];
    bytes[0] = data[++index];

    float result = *(float *)bytes;
    LOG_DEBUG("float was %f\n", result);

    return index;
}

/*
CONSTANT_Long_info {
    u1 tag;
    u4 high_bytes;
    u4 low_bytes;
}
*/
int parse_next_long(int index, const uint8_t *data) {

    LOG_DEBUG("(long)\n");

    uint8_t bytes[8];
    bytes[7] = data[++index];
    bytes[6] = data[++index];
    bytes[5] = data[++index];
    bytes[4] = data[++index];
    bytes[3] = data[++index];
    bytes[2] = data[++index];
    bytes[1] = data[++index];
    bytes[0] = data[++index];

    long result = *(long *)bytes;
    LOG_DEBUG("long was %ld\n", result);

    return index;
}

/*
CONSTANT_Double_info {
    u1 tag;
    u4 high_bytes;
    u4 low_bytes;
}
*/
int parse_next_double(int index, const uint8_t *data) {

    LOG_DEBUG("(double)\n");

    uint8_t bytes[8];
    bytes[7] = data[++index];
    bytes[6] = data[++index];
    bytes[5] = data[++index];
    bytes[4] = data[++index];
    bytes[3] = data[++index];
    bytes[2] = data[++index];
    bytes[1] = data[++index];
    bytes[0] = data[++index];

    double result = *(double *)bytes;
    LOG_DEBUG("double was %f\n", result);

    return index;
}

/*
CONSTANT_Class_info {
    u1 tag;
    u2 name_index;
}
 */
int parse_next_class_ref(int index, const uint8_t *data) {

    LOG_DEBUG("(class ref)\n");

    uint8_t name_index_msb = data[++index];
    uint8_t name_index_lsb = data[++index];
    int name_index = name_index_msb * 16 + name_index_lsb;
    LOG_DEBUG("name_index was %d\n", name_index);

    return index;
}

/*
CONSTANT_String_info {
    u1 tag;
    u2 string_index;
}
*/
int parse_next_string(int index, const uint8_t *data) {

    LOG_DEBUG("(string)\n");

    uint8_t string_index_msb = data[++index];
    uint8_t string_index_lsb = data[++index];
    int string_index = string_index_msb * 16 + string_index_lsb;
    LOG_DEBUG("string_index was %d\n", string_index);

    return index;
}

/*
CONSTANT_???ref_info {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
}
*/
int parse_next_ref(int index, const uint8_t *data) {
    uint8_t class_index_msb = data[++index];
    uint8_t class_index_lsb = data[++index];
    int class_index = class_index_msb * 16 + class_index_lsb;
    LOG_DEBUG("class_index was %d\n", class_index);

    uint8_t name_and_type_index_msb = data[++index];
    uint8_t name_and_type_index_lsb = data[++index];
    int name_and_type_index = name_and_type_index_msb * 16 + name_and_type_index_lsb;
    LOG_DEBUG("name and type index was %d\n", name_and_type_index);

    return index;
}

/*
CONSTANT_Fieldref_info {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
}
*/
int parse_next_field_ref(int index, const uint8_t *data) {
    LOG_DEBUG("(field ref)\n");
    return parse_next_ref(index, data);
}

/*
CONSTANT_Methodref_info {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
}
*/
int parse_next_method_ref(int index, const uint8_t *data) {
    LOG_DEBUG("(method ref)\n");
    return parse_next_ref(index, data);
}

/*
CONSTANT_InterfaceMethodref_info {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
}
*/
int parse_next_iface_method_ref(int index, const uint8_t *data) {
    LOG_DEBUG("(interface method ref)\n");
    return parse_next_ref(index, data);
}

/*
CONSTANT_NameAndType_info {
    u1 tag;
    u2 name_index;
    u2 descriptor_index;
}
*/
int parse_next_name_and_type(int index, const uint8_t *data) {

    LOG_DEBUG("(name and type constant)\n");

    uint8_t name_index_msb = data[++index];
    uint8_t name_index_lsb = data[++index];
    int name_index = name_index_msb * 16 + name_index_lsb;
    LOG_DEBUG("name_index was %d\n", name_index);

    uint8_t desc_index_msb = data[++index];
    uint8_t desc_index_lsb = data[++index];
    int desc_index = desc_index_msb * 16 + desc_index_lsb;
    LOG_DEBUG("desc_index was %d\n", desc_index);

    return index;
}

/*
CONSTANT_MethodHandle_info {
    u1 tag;
    u1 reference_kind;
    u2 reference_index;
}
*/
int parse_next_method_handle(int index, const uint8_t *data) {

    LOG_DEBUG("(method handle)\n");

    uint8_t reference_kind = data[++index];
    LOG_DEBUG("reference_kind was %d\n", reference_kind);

    uint8_t reference_index_msb = data[++index];
    uint8_t reference_index_lsb = data[++index];
    int reference_index = reference_index_msb * 16 + reference_index_lsb;
    LOG_DEBUG("reference_index was %d\n", reference_index);

    return index;
}