#include "bifit.h"
#include "load_class_utils.h"

unsigned int load_next_field(unsigned int index, const uint8_t *data, bifit_constant_pool_entry_t entries[], bifit_field_t *out);

unsigned int load_field_access_flags(unsigned int index, const uint8_t *data, bifit_field_access_flags_t *out);

void load_fields(unsigned int start_index, const uint8_t *data, bifit_class_t *out) {

    unsigned int index = start_index;

    out->fields.field_count = parse_integer_u2(index, data);
    LOG_DEBUG("load_fields num of fields: %d\n", out->fields.field_count);
    index += 2;

    out->fields.field_array = malloc(sizeof(bifit_field_t) * out->fields.field_count);

    for (int i = 0; i < out->fields.field_count; ++i) {
        index = load_next_field(index, data, out->constant_pool.entries, &out->fields.field_array[i]);
    }

    out->fields.size_in_bytes = index - start_index;
}

/*
field_info {
    u2             access_flags;
    u2             name_index;
    u2             descriptor_index;
    u2             attributes_count;
    attribute_info attributes[attributes_count];
}
*/
unsigned int load_next_field(unsigned int index, const uint8_t *data, bifit_constant_pool_entry_t entries[], bifit_field_t *out) {

    index = load_field_access_flags(index, data, &out->access_flags);

    int identifier_name_index = parse_integer_u2(index, data);
    load_identifier_by_name_index(identifier_name_index, entries, &out->name_identifier);
    index += 2;

    int descriptor_name_index = parse_integer_u2(index, data);
    load_identifier_by_name_index(descriptor_name_index, entries, &out->descriptor_identifier);
    index += 2;

    out->attributes_count = parse_integer_u2(index, data);
    out->attributes = malloc(sizeof(bifit_attribute_t) * out->attributes_count);
    for (int i = 0; i < out->attributes_count; ++i) {
        index = load_attribute(index, data, entries, &out->attributes[i]);
    }

    return index;
}

unsigned int load_field_access_flags(unsigned int index, const uint8_t *data, bifit_field_access_flags_t *out) {
    uint8_t msb = data[index];
    uint8_t lsb = data[index + 1];

    out->is_public = (0x01 & lsb) ? true : false;
    out->is_private = (0x02 & lsb) ? true : false;
    out->is_protected = (0x04 & lsb) ? true : false;
    out->is_static = (0x08 & lsb) ? true : false;
    out->is_final = (0x10 & lsb) ? true : false;
    out->is_volatile = (0x40 & lsb) ? true : false;
    out->is_transient = (0x80 & lsb) ? true : false;
    out->is_synthetic = (0x10 & msb) ? true : false;
    out->is_enum = (0x40 & msb) ? true : false;

    return index + 2;
}