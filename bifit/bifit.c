#include "load_class/load_class.h"
#include "string.h"

bool identifier_matches_string(bifit_identifier_t *identifier, char *string);
bifit_class_t *find_class_by_name(bifit_class_t *list, char *identifier);

void bifit_run() {

    bifit_class_t *class_list = bifit_load_embedded_classes();
    LOG_DEBUG("classes loaded!\n");

    bifit_class_t *main_class = find_class_by_name(class_list, bifit_main_class_identifier);
    if (main_class == NULL) {
        printf("ERROR: main class %s not found in loaded class_list!\n", bifit_main_class_identifier);
        exit(1);
    }
    LOG_DEBUG("main class found: %s\n", bifit_main_class_identifier);
}

bool identifier_matches_string(bifit_identifier_t *identifier, char *string) {
    LOG_DEBUG("identifier_matches_string checking identifier ");
    log_bifit_identifier(identifier);
    LOG_DEBUG("\n");
    if (identifier->identifier_length != strlen(string)) {
        return false;
    }

    for (int i = 0; i < identifier->identifier_length; ++i) {
        if ((identifier->identifier)[i] != string[i]) {
            return false;
        }
    }

    return true;
}

bifit_class_t *find_class_by_name(bifit_class_t *class_list, char *identifier) {
    for (int i = 0; i < bifit_embedded_class_files_size; ++i) {
        if (identifier_matches_string(&(class_list[i].this_class), identifier)) {
            return &class_list[i];
        }
    }

    return NULL;
}
