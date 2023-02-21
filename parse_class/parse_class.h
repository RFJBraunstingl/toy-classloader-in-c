#define LOG_DEBUG printf

#include "header.h"
#include "constants.h"
#include "helpers.h"
#include "interfaces.h"
#include "fields.h"
#include "methods.h"
#include "attributes.h"

void parse_class(const uint8_t data[])
{
    parse_class_header(data);
    LOG_DEBUG("\n");

    int index = parse_constant_pool(data);
    LOG_DEBUG("\n");

    index = parse_access_flags(index, data);
    index = parse_this_class(index, data);
    index = parse_super_class(index, data);
    LOG_DEBUG("\n");

    index = parse_interfaces(index, data);
    LOG_DEBUG("\n");

    index = parse_fields(index, data);
    LOG_DEBUG("\n");

    index = parse_methods(index, data);
    LOG_DEBUG("\n");

    index = parse_attributes(index, data);
    LOG_DEBUG("\n");

    LOG_DEBUG("parsed %d bytes of data for class file - success\n", index);
}