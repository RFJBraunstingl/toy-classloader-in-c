
#include "classes_combined.h"
#include "parse_class/parse_class.h"
#include "util/bifit_string_util.h"

/**
 * Loop through the embedded class files
 * get the identifier of the class
 * return an array where the index points to the identifier of the class
 */
bifit_class_identifier_t *bifit_class_index_build() {

    bifit_class_identifier_t *class_index = malloc(sizeof(bifit_class_identifier_t) * bifit_embedded_class_files_size);

    for (int i = 0; i < bifit_embedded_class_files_size; i++) {
        uint8_t *class_file = bifit_embedded_class_files[i];
        scan_class_identifier(class_file, &class_index[i]);
    }

    return class_index;
}

void load_class_identifier(int index, const uint8_t *data, bifit_const_pool_entry_t entries[], bifit_class_identifier_t *out) {
    LOG_DEBUG("\nload_class_identifier\n");
    int class_index = parse_integer_u2(index, data);
    LOG_DEBUG("class_index: %d\n", class_index);

    bifit_const_pool_entry_t this_entry = entries[class_index - 1];
    LOG_DEBUG("class identifier index: %d\n", this_entry.name_index);

    bifit_const_pool_entry_t this_class_entry = entries[this_entry.name_index - 1];
    out->class_identifier = this_class_entry.utf8_str;
    out->class_identifier_length = this_class_entry.utf8_str_len;

    LOG_DEBUG("result of load_class_identifier was: ");
    for (int i = 0; i < out->class_identifier_length; i++) {
        LOG_DEBUG("%c", out->class_identifier[i]);
    }
    LOG_DEBUG("\n");
}

void bifit_load_class(const uint8_t *data, bifit_class_t *out) {
    int given_const_pool_count = parse_integer_u2(8, data);
    int real_const_pool_count = given_const_pool_count - 1;

    int byte_index = 10;
    bifit_const_pool_entry_t entries[real_const_pool_count];

    for (int i = 0; i < real_const_pool_count; i++) {
        LOG_DEBUG("\nparsing const entry %d\n", i+1);
        byte_index = parse_next_constant_pool_entry(byte_index, data, &entries[i]);
    }

    // byte_index = parse_access_flags(byte_index, data);
    byte_index += 2;

    load_class_identifier(byte_index, data, entries, &(out->this_class));
    byte_index += 2;
    load_class_identifier(byte_index, data, entries, &(out->super_class));
    byte_index += 2;

    byte_index = parse_interfaces(byte_index, data);


}

bifit_class_t *bifit_load_embedded_classes() {

    unsigned int number_of_classes = bifit_embedded_class_files_size;

    bifit_class_t *classes = malloc(sizeof(bifit_class_identifier_t) * number_of_classes);

    for (int i = 0; i < number_of_classes; i++) {
        uint8_t *class_file = bifit_embedded_class_files[i];
        bifit_load_class(class_file, &classes[i]);
    }

    return classes;
}

void bifit_run() {
    bifit_class_identifier_t *class_index = bifit_class_index_build();
    LOG_DEBUG("class_index scan was complete!\n");

    LOG_DEBUG("idx: identifier\n");
    for (int i = 0; i < bifit_embedded_class_files_size; ++i) {
        bifit_class_identifier_t id = class_index[i];
        LOG_DEBUG("%03d: ", i);
        log_string_with_length(id.class_identifier, id.class_identifier_length);
    }

    bifit_load_embedded_classes();
    // bifit_class_index_find_identifier(bifit_main_class_identifier);
    // bifit_execute_main_method();
}