#include "bifit.h"

#define BIFIT_CLASS_IDENTIFIER_SIZE_IN_BYTES 2

void load_class_identifier(unsigned int index, const uint8_t *data, bifit_constant_pool_entry_t entries[], bifit_identifier_t *out) {
    LOG_DEBUG("load_class_identifier\n");
    unsigned int class_index = parse_integer_u2(index, data);
    LOG_DEBUG("class_index: %d\n", class_index);

    bifit_constant_pool_entry_t this_entry = entries[class_index - 1];
    LOG_DEBUG("class identifier index: %d\n", this_entry.name_index);

    bifit_constant_pool_entry_t this_class_entry = entries[this_entry.name_index - 1];
    out->class_identifier = this_class_entry.utf8_str;
    out->class_identifier_length = this_class_entry.utf8_str_len;

    LOG_DEBUG("result of load_class_identifier was: ");
    for (int i = 0; i < out->class_identifier_length; i++) {
        LOG_DEBUG("%c", out->class_identifier[i]);
    }
    LOG_DEBUG("\n\n");
}