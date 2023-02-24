#include "bifit.h"

unsigned int load_method(unsigned int index, const uint8_t *data, bifit_constant_pool_entry_t entries[], bifit_method_t *out);

void load_methods(unsigned int start_index, const uint8_t *data, bifit_constant_pool_entry_t entries[], bifit_methods_t *out) {

    unsigned int index = start_index;



    out->size_in_bytes = start_index - index;
}

/*
method_info {
    u2             access_flags;
    u2             name_index;
    u2             descriptor_index;
    u2             attributes_count;
    attribute_info attributes[attributes_count];
}
*/
unsigned int load_method(unsigned int index, const uint8_t *data, bifit_constant_pool_entry_t entries[], bifit_method_t *out) {


}