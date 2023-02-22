
#include "classes_combined.h"
#include "parse_class/parse_class.h"
#include "util/bifit_string_util.h"

/**
 * Loop through the embedded class files
 * get the identifier of the class
 * return an array where the index points to the identifier of the class
 */
class_identifier_t *bifit_class_index_build() {

    class_identifier_t *class_index = malloc(sizeof(class_identifier_t) * bifit_embedded_class_files_size);

    for (int i = 0; i < bifit_embedded_class_files_size; i++) {
        uint8_t *class_file = bifit_embedded_class_files[i];
        scan_class_identifier(class_file, &class_index[i]);
    }

    return class_index;
}

void bifit_run() {
    class_identifier_t *class_index = bifit_class_index_build();
    LOG_DEBUG("class_index scan was complete!\n");

    LOG_DEBUG("idx: identifier\n");
    for (int i = 0; i < bifit_embedded_class_files_size; ++i) {
        class_identifier_t id = class_index[i];
        LOG_DEBUG("%03d: ", i);
        log_string_with_length(id.class_identifier, id.class_identifier_length);
    }

    // bifit_class_index_find_identifier(bifit_main_class_identifier);
    // bifit_execute_main_method();
}