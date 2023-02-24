#include "bifit.h"

#define BIFIT_CLASS_HEADER_SIZE_IN_BYTES 8

void load_class_header(const uint8_t data[], bifit_class_header_t *out) {

    // major version at byte index 4-5
    out->major_version = parse_integer_u2(4, data);
    // minor version at byte index 6-7
    out->minor_version = parse_integer_u2(6, data);
    // guess java version
    out->java_version = out->major_version - 44;
}