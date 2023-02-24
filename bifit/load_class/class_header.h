#include "bifit.h"

#define BIFIT_CLASS_HEADER_SIZE_IN_BYTES 8

bifit_class_header_t *load_class_header(const uint8_t data[]) {

    bifit_class_header_t *result = malloc(sizeof(bifit_class_header_t));

    // major version at byte index 4-5
    result->major_version = parse_integer_u2(4, data);
    // minor version at byte index 6-7
    result->minor_version = parse_integer_u2(6, data);

    // guess java version
    result->java_version = result->major_version - 44;

    return result;
}