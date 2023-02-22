
#include "classes_combined.h"

typedef uint8_t * identifier_p;

/**
 * Loop through the embedded class files
 * get the identifier of the class
 * return an array where the index points to the identifier of the class
 */
void bifit_class_index_build() {

    identifier_p identifier_pointer_array[bifit_embedded_class_files_size];

    for (int i = 0; i < bifit_embedded_class_files_size; i++) {
        uint8_t *class_file = bifit_embedded_class_files[i];

    }
}

void bifit_run() {
    bifit_class_index_build();
    // bifit_class_index_find_identifier(bifit_main_class_identifier);
    // bifit_execute_main_method();
}