#define LOG_DEBUG printf

#include "header.h"
#include "constants.h"
#include "helpers.h"
#include "interfaces.h"
#include "fields.h"
#include "methods.h"
#include "attributes.h"

void parse_class(const uint8_t data[]) {

    parse_class_header(data);
    LOG_DEBUG("\n");

    int index = parse_constant_pool(data);
    LOG_DEBUG("\n");

    index = parse_access_flags(index, data);
    index = parse_this_class(index, data);
    index = parse_super_class(index, data);
    LOG_DEBUG("\n");

    index = parse_interfaces(index, data);
    LOG_DEBUG("\n");

    index = parse_fields(index, data);
    LOG_DEBUG("\n");

    index = parse_methods(index, data);
    LOG_DEBUG("\n");

    index = parse_attributes(index, data);
    LOG_DEBUG("\n");

    LOG_DEBUG("parsed %d bytes of data for class file - success\n", index);
}

typedef struct class_identifier {

    const uint8_t *class_identifier;
    int class_identifier_length;

} class_identifier_t;

int scan_class_identifier(const uint8_t data[], class_identifier_t *out) {
    int given_const_pool_count = parse_integer_u2(8, data);
    int real_const_pool_count = given_const_pool_count - 1;

    int byte_index = 10;
    const_pool_entry_t entries[real_const_pool_count];

    for (int i = 0; i < real_const_pool_count; i++) {
        byte_index = parse_next_constant_pool_entry(byte_index, data, &entries[i]);
    }

    // byte_index = parse_access_flags(byte_index, data);
    byte_index += 2;

    int this_class_index = parse_integer_u2(byte_index, data);
    LOG_DEBUG("scan_class_identifier got this_index %d\n", this_class_index);

    const_pool_entry_t this_entry = entries[this_class_index - 1];
    LOG_DEBUG("class identifier index: %d\n", this_entry.name_index);

    return 0;
}
