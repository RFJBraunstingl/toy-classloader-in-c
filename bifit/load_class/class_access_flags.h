#include "bifit.h"

#define BIFIT_CLASS_ACCESS_FLAGS_SIZE_IN_BYTES 2

void load_class_access_flags(unsigned int index, const uint8_t data[], bifit_class_access_flags_t *out) {
    uint8_t msb = data[index];
    uint8_t lsb = data[index + 1];

    out->is_public = (0x01 & lsb) ? true : false;
    out->is_final = (0x10 & lsb) ? true : false;
    out->is_super = (0x20 & lsb) ? true : false;
    out->is_interface = (0x02 & msb) ? true : false;
    out->is_abstract = (0x04 & msb) ? true : false;
    out->is_synthetic = (0x10 & msb) ? true : false;
    out->is_annotation = (0x20 & msb) ? true : false;
    out->is_enum = (0x40 & msb) ? true : false;
    out->is_module = (0x80 & msb) ? true : false;
}