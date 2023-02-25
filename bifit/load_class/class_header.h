#ifndef BIFIT_LOAD_CLASS_HEADER_H_
#define BIFIT_LOAD_CLASS_HEADER_H_

#include "bifit.h"
#include "load_class_utils.h"

#define BIFIT_MINOR_VERSION_BYTE_OFFSET 4
#define BIFIT_MAJOR_VERSION_BYTE_OFFSET 6
#define BIFIT_CLASS_HEADER_SIZE_IN_BYTES 8
#define BIFIT_JAVA_MAJOR_VERSION_OFFSET 44

void load_class_header(const uint8_t data[], bifit_class_header_t *out) {

    // minor version at byte index 4-5
    out->minor_version = parse_integer_u2(BIFIT_MINOR_VERSION_BYTE_OFFSET, data);
    LOG_DEBUG("load_class_header minor_version: %d\n", out->minor_version);
    // major version at byte index 6-7
    out->major_version = parse_integer_u2(BIFIT_MAJOR_VERSION_BYTE_OFFSET, data);
    LOG_DEBUG("load_class_header major_version: %d\n", out->major_version);
    // guess java version
    out->java_version = out->major_version - BIFIT_JAVA_MAJOR_VERSION_OFFSET;
    LOG_DEBUG("load_class_header java_version: %d\n", out->java_version);
}

#endif