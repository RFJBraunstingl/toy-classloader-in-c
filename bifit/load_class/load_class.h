#include "bifit.h"

#include "class_header.h"
#include "constant_pool.h"
#include "class_access_flags.h"
#include "class_identifier.h"
#include "interfaces.h"
#include "fields.h"
#include "methods.h"

/* prototypes */
bifit_class_t *bifit_load_embedded_classes();
void bifit_load_class(const uint8_t *data, bifit_class_t *out);

/* impl */
bifit_class_t *bifit_load_embedded_classes() {

    unsigned int number_of_classes = bifit_embedded_class_files_size;

    bifit_class_t *classes = malloc(sizeof(struct bifit_identifier) * number_of_classes);

    for (int i = 0; i < number_of_classes; i++) {
        uint8_t *class_file = bifit_embedded_class_files[i];
        bifit_load_class(class_file, &classes[i]);
    }

    return classes;
}

void bifit_load_class(const uint8_t *data, bifit_class_t *out) {

    load_class_header(data, &out->class_header);
    load_constant_pool(data, &out->constant_pool);

    unsigned int byte_index = BIFIT_CLASS_HEADER_SIZE_IN_BYTES + out->constant_pool.size_in_bytes;

    load_class_access_flags(byte_index, data, &out->access_flags);
    byte_index += BIFIT_CLASS_ACCESS_FLAGS_SIZE_IN_BYTES;

    load_class_identifier(byte_index, data, out->constant_pool.entries, &(out->this_class));
    byte_index += BIFIT_CLASS_IDENTIFIER_SIZE_IN_BYTES;
    load_class_identifier(byte_index, data, out->constant_pool.entries, &(out->super_class));
    byte_index += BIFIT_CLASS_IDENTIFIER_SIZE_IN_BYTES;

    load_interfaces(byte_index, data, out);
    byte_index += out->interfaces.size_in_bytes;

    load_fields(byte_index, data, out);
    byte_index += out->fields.size_in_bytes;

    load_methods(byte_index, data, out->constant_pool.entries, &(out->methods), out);
    byte_index += out->methods.size_in_bytes;

    LOG_DEBUG("after loading methods ");
    log_bifit_identifier(&(out->this_class));
    LOG_DEBUG("\n");
}

