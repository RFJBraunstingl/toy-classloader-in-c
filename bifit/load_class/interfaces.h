#include "bifit.h"

void load_interfaces(unsigned int start_index, const uint8_t data[], bifit_class_t *out) {
    LOG_DEBUG("load_interfaces\n");
    unsigned int byte_index = start_index;

    out->interfaces.interface_count = parse_integer_u2(byte_index, data);
    LOG_DEBUG("interface_count: %d\n", out->interfaces.interface_count);
    byte_index += 2;

    out->interfaces.identifiers = malloc(
            sizeof(bifit_identifier_t) * out->interfaces.interface_count
    );

    for (int i = 0; i < out->interfaces.interface_count; ++i) {
        load_class_identifier(
                byte_index,
                data,
                out->constant_pool.entries,
                &out->interfaces.identifiers[i]
        );
    }

    out->interfaces.size_in_bytes = byte_index - start_index;
}