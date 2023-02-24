#define LOG_DEBUG printf

#ifndef BIFIT_STD_H_
#define BIFIT_STD_H_

#include <stdlib.h>
#include <stdio.h>

#include "classes_combined.h"

#include "./util/bifit_string_util.h"
#include "./util/bifit_number_util.h"

typedef struct {

    int major_version;
    int minor_version;
    int java_version;

} bifit_class_header_t;

typedef struct {

    // every constant has a type (/tag)
    uint8_t type;

    // for utf8 constants
    const uint8_t *utf8_str;
    int utf8_str_len;

    // for names and descriptions
    int name_index;
    int desc_index;

    // for whole numbers
    long long_value;

    // for floating point
    double double_value;

    // for class refs
    int class_index;
    int name_and_type_index;

    // for method handles
    uint8_t ref_type;
    int ref_index;

} bifit_constant_pool_entry_t;

typedef struct {

    unsigned int entry_count;
    unsigned int size_in_bytes;
    bifit_constant_pool_entry_t *entries;

} bifit_constant_pool_t;

typedef struct {

    const uint8_t *class_identifier;
    int class_identifier_length;

} bifit_class_identifier_t;

typedef struct {

    unsigned int interface_count;
    unsigned int size_in_bytes;
    bifit_class_identifier_t *interface_identifiers;

} bifit_class_interfaces_t;

typedef struct {

    bifit_class_header_t class_header;
    bifit_constant_pool_t constant_pool;
    bifit_class_identifier_t this_class;
    bifit_class_identifier_t super_class;
    bifit_class_interfaces_t interfaces;

} bifit_class_t;

void bifit_run();

#endif