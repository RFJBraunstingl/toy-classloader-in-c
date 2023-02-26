#include "bifit.h"

#define BIFIT_CLASS_IDENTIFIER_SIZE_IN_BYTES 2

void load_class_identifier(unsigned int index, const uint8_t *data, bifit_constant_pool_entry_t entries[], bifit_identifier_t *out) {
    LOG_DEBUG("load_class_identifier\n");
    unsigned int class_index = parse_integer_u2(index, data);
    LOG_DEBUG("class_index: %d\n", class_index);

    bifit_constant_pool_entry_t this_entry = entries[class_index - 1];
    LOG_DEBUG("class identifier index: %d\n", this_entry.name_index);

    bifit_constant_pool_entry_t this_class_entry = entries[this_entry.name_index - 1];
    out->identifier = this_class_entry.utf8_str;
    out->identifier_length = this_class_entry.utf8_str_len;

    LOG_DEBUG("result of load_class_identifier was: ");
    log_bifit_identifier(out);
    LOG_DEBUG("\n\n");
}