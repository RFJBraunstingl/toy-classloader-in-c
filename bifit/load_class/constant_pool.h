#include "bifit.h"

int load_next_constant_pool_entry(int index, const uint8_t *data, bifit_constant_pool_entry_t *out);

int load_next_utf8(int index, const uint8_t *data, bifit_constant_pool_entry_t *out);

int load_next_integer(int index, const uint8_t *data, bifit_constant_pool_entry_t *out);

int load_next_float(int index, const uint8_t *data, bifit_constant_pool_entry_t *out);

int load_next_long(int index, const uint8_t *data, bifit_constant_pool_entry_t *out);

int load_next_double(int index, const uint8_t *data, bifit_constant_pool_entry_t *out);

int load_next_class_ref(int index, const uint8_t *data, bifit_constant_pool_entry_t *out);

int load_next_string(int index, const uint8_t *data, bifit_constant_pool_entry_t *out);

int load_next_ref(int index, const uint8_t *data, bifit_constant_pool_entry_t *out);

int load_next_field_ref(int index, const uint8_t *data, bifit_constant_pool_entry_t *out);

int load_next_method_ref(int index, const uint8_t *data, bifit_constant_pool_entry_t *out);

int load_next_iface_method_ref(int index, const uint8_t *data, bifit_constant_pool_entry_t *out);

int load_next_name_and_type(int index, const uint8_t *data, bifit_constant_pool_entry_t *out);

int load_next_method_handle(int index, const uint8_t *data, bifit_constant_pool_entry_t *out);


#define BIFIT_CONSTANT_POOL_START_INDEX 8
void load_constant_pool(const uint8_t data[], bifit_constant_pool_t *out) {

    unsigned int const_pool_size = parse_integer_u2(BIFIT_CONSTANT_POOL_START_INDEX, data);
    unsigned int number_of_entries = const_pool_size - 1;
    LOG_DEBUG("dealing with a constant pool of size %d\n", number_of_entries);

    out->entries = malloc(
            sizeof(bifit_constant_pool_entry_t) * number_of_entries
    );
    out->entry_count = number_of_entries;

    int byte_index = 10;
    for (int i = 1; i < const_pool_size; i++) {
        LOG_DEBUG("reading constant pool entry %d\n", i);
        byte_index = load_next_constant_pool_entry(
                byte_index,
                data,
                &out->entries[i - 1]
        );
        LOG_DEBUG("\n");
    }

    out->size_in_bytes = byte_index - BIFIT_CONSTANT_POOL_START_INDEX;
}

int load_next_constant_pool_entry(int index, const uint8_t *data, bifit_constant_pool_entry_t *out) {
    uint8_t tag = data[index++];
    LOG_DEBUG("constant has tag %d ", tag);

    switch (tag) {

        case 1:
            return load_next_utf8(index, data, out);

        case 3:
            return load_next_integer(index, data, out);

        case 4:
            return load_next_float(index, data, out);

        case 5:
            return load_next_long(index, data, out);

        case 6:
            return load_next_double(index, data, out);

        case 7:
            return load_next_class_ref(index, data, out);

        case 8:
            return load_next_string(index, data, out);

        case 9:
            return load_next_field_ref(index, data, out);

        case 10:
            return load_next_method_ref(index, data, out);

        case 11:
            return load_next_iface_method_ref(index, data, out);

        case 12:
            return load_next_name_and_type(index, data, out);

        case 15:
            return load_next_method_handle(index, data, out);

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
int load_next_utf8(int index, const uint8_t *data, bifit_constant_pool_entry_t *out) {
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
int load_next_integer(int index, const uint8_t *data, bifit_constant_pool_entry_t *out) {

    LOG_DEBUG("(int)\n");

    uint8_t bytes[4];
    bytes[3] = data[index++];
    bytes[2] = data[index++];
    bytes[1] = data[index++];
    bytes[0] = data[index++];

    out->long_value = *(int *) bytes;
    LOG_DEBUG("integer was %ld\n", out->long_value);

    return index;
}

/*
CONSTANT_Float_info {
    u1 tag;
    u4 bytes;
}
*/
int load_next_float(int index, const uint8_t *data, bifit_constant_pool_entry_t *out) {

    LOG_DEBUG("(float)\n");

    uint8_t bytes[4];
    bytes[3] = data[index++];
    bytes[2] = data[index++];
    bytes[1] = data[index++];
    bytes[0] = data[index++];

    out->double_value = *(float *) bytes;
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
int load_next_long(int index, const uint8_t *data, bifit_constant_pool_entry_t *out) {

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

    out->long_value = *(long *) bytes;
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
int load_next_double(int index, const uint8_t *data, bifit_constant_pool_entry_t *out) {

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

    out->double_value = *(double *) bytes;
    LOG_DEBUG("double was %f\n", out->double_value);

    return index;
}

/*
CONSTANT_Class_info {
    u1 tag;
    u2 name_index;
}
 */
int load_next_class_ref(int index, const uint8_t *data, bifit_constant_pool_entry_t *out) {

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
int load_next_string(int index, const uint8_t *data, bifit_constant_pool_entry_t *out) {

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
int load_next_ref(int index, const uint8_t *data, bifit_constant_pool_entry_t *out) {
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
int load_next_field_ref(int index, const uint8_t *data, bifit_constant_pool_entry_t *out) {
    LOG_DEBUG("(field ref)\n");
    return load_next_ref(index, data, out);
}

/*
CONSTANT_Methodref_info {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
}
*/
int load_next_method_ref(int index, const uint8_t *data, bifit_constant_pool_entry_t *out) {
    LOG_DEBUG("(method ref)\n");
    return load_next_ref(index, data, out);
}

/*
CONSTANT_InterfaceMethodref_info {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
}
*/
int load_next_iface_method_ref(int index, const uint8_t *data, bifit_constant_pool_entry_t *out) {
    LOG_DEBUG("(interface method ref)\n");
    return load_next_ref(index, data, out);
}

/*
CONSTANT_NameAndType_info {
    u1 tag;
    u2 name_index;
    u2 descriptor_index;
}
*/
int load_next_name_and_type(int index, const uint8_t *data, bifit_constant_pool_entry_t *out) {

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
int load_next_method_handle(int index, const uint8_t *data, bifit_constant_pool_entry_t *out) {

    LOG_DEBUG("(method handle)\n");

    out->ref_type = data[index++];
    LOG_DEBUG("reference_kind was %d\n", out->ref_type);

    out->ref_index = parse_integer_u2(index, data);
    LOG_DEBUG("reference_index was %d\n", out->ref_index);

    return index + 2;
}