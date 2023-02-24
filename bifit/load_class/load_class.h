#include "bifit.h"

void bifit_load_class(const uint8_t *data, bifit_class_t *out) {
    int given_const_pool_count = parse_integer_u2(8, data);
    int real_const_pool_count = given_const_pool_count - 1;

    int byte_index = 10;
    const_pool_entry_t entries[real_const_pool_count];

    for (int i = 0; i < real_const_pool_count; i++) {
        LOG_DEBUG("\nparsing const entry %d\n", i+1);
        byte_index = parse_next_constant_pool_entry(byte_index, data, &entries[i]);
    }

    // byte_index = parse_access_flags(byte_index, data);
    byte_index += 2;

    load_class_identifier(byte_index, data, entries, &(out->this_class));
    byte_index += 2;
    load_class_identifier(byte_index, data, entries, &(out->super_class));
    byte_index += 2;

    byte_index = parse_interfaces(byte_index, data);


}
