#include "bifit.h"

void load_interfaces(int start_index, const uint8_t data[], bifit_class_t *out) {
    LOG_DEBUG("load_interfaces\n");
    int byte_index = start_index;

    out->interfaces.interface_count = parse_integer_u2(byte_index, data);
    LOG_DEBUG("interface_count: %d\n", out->interfaces.interface_count);
    byte_index += 2;

    out->interfaces.interface_identifiers = malloc(
            sizeof(bifit_class_identifier_t) * out->interfaces.interface_count
    );

    for (int i = 0; i < out->interfaces.interface_count; ++i) {

    }
}