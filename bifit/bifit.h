#define LOG_DEBUG printf

#ifndef BIFIT_STD_H_
#define BIFIT_STD_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "classes_combined.h"

/**
 * generic types
 */
typedef struct {

    const uint8_t *class_identifier;
    int class_identifier_length;

} bifit_identifier_t;

typedef struct {

    bifit_identifier_t name;
    int length_in_bytes;
    const uint8_t *data;

} bifit_attribute_t;

/**
 * actual class types
 */
typedef struct {

    unsigned int major_version;
    unsigned int minor_version;
    unsigned int java_version;

} bifit_class_header_t;

typedef struct {

    // every constant has a type (/tag)
    uint8_t type;

    // for utf8 constants
    const uint8_t *utf8_str;
    unsigned int utf8_str_len;

    // for names and descriptions
    unsigned int name_index;
    unsigned int desc_index;

    // for whole numbers
    long long_value;

    // for floating point
    double double_value;

    // for class refs
    unsigned int class_index;
    unsigned int name_and_type_index;

    // for method handles
    uint8_t ref_type;
    unsigned int ref_index;

} bifit_constant_pool_entry_t;

typedef struct {

    unsigned int entry_count;
    unsigned int size_in_bytes;
    bifit_constant_pool_entry_t *entries;

} bifit_constant_pool_t;

typedef struct {

    bool is_public;
    bool is_final;
    bool is_super;
    bool is_interface;
    bool is_abstract;
    bool is_synthetic;
    bool is_annotation;
    bool is_enum;
    bool is_module;

} bifit_class_access_flags_t;

typedef struct {

    unsigned int interface_count;
    unsigned int size_in_bytes;
    bifit_identifier_t *identifiers;

} bifit_class_interfaces_t;

typedef struct {

    bool is_public;
    bool is_private;
    bool is_protected;
    bool is_static;
    bool is_final;
    bool is_volatile;
    bool is_transient;
    bool is_synthetic;
    bool is_enum;

} bifit_field_access_flags_t;

typedef struct {

    bifit_field_access_flags_t access_flags;
    bifit_identifier_t name;
    bifit_identifier_t descriptor;
    unsigned int attributes_count;
    bifit_attribute_t *attributes;

} bifit_field_t;

typedef struct {

    unsigned int field_count;
    unsigned int size_in_bytes;
    bifit_field_t *field_array;

} bifit_fields_t;

typedef struct {

    bool is_public;
    bool is_private;
    bool is_protected;
    bool is_static;
    bool is_final;
    bool is_synchronized;
    bool is_bridge;
    bool is_varargs;
    bool is_native;
    bool is_abstract;
    bool is_strict;
    bool is_synthetic;

} bifit_method_access_flags_t;

typedef struct {

    unsigned int max_stack;
    unsigned int max_locals;
    unsigned int byte_code_length;
    const uint8_t *byte_code;

} bifit_method_code_t;

typedef struct {

    bifit_method_access_flags_t access_flags;
    bifit_identifier_t name;
    bifit_identifier_t descriptor;
    unsigned int attributes_count;
    bifit_attribute_t *attributes;

    bifit_method_code_t code;

} bifit_method_t;

typedef struct {

    unsigned int method_count;
    unsigned int size_in_bytes;
    bifit_method_t *method_array;

} bifit_methods_t;

/**
 * putting it all together
 */
typedef struct {

    bifit_class_header_t class_header;
    bifit_constant_pool_t constant_pool;
    bifit_identifier_t this_class;
    bifit_identifier_t super_class;
    bifit_class_interfaces_t interfaces;
    bifit_class_access_flags_t access_flags;
    bifit_fields_t fields;
    bifit_methods_t methods;

} bifit_class_t;

/**
 * define interface methods
 */
void bifit_run();

#endif