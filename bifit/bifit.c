#include "load_class/load_class.h"

void bifit_run() {
    /*
     * bifit_class_identifier_t *class_index = bifit_class_index_build();
    LOG_DEBUG("class_index scan was complete!\n");

    LOG_DEBUG("idx: identifier\n");
    for (int i = 0; i < bifit_embedded_class_files_size; ++i) {
        bifit_class_identifier_t id = class_index[i];
        LOG_DEBUG("%03d: ", i);
        log_string_with_length(id.class_identifier.h, id.class_identifier_length);
    }*/

    bifit_load_embedded_classes();
    // bifit_class_index_find_identifier(bifit_main_class_identifier);
    // bifit_execute_main_method();
}