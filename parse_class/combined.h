#include "header.h"
#include "constants.h"
#include "helpers.h"
#include "interfaces.h"
#include "fields.h"
#include "methods.h"
#include "attributes.h"

void parse_class(const uint8_t data[])
{
    int index = parse_constant_pool(data);
    printf("\n");

    index = parse_access_flags(index, data);
    index = parse_this_class(index, data);
    index = parse_super_class(index, data);
    printf("\n");

    index = parse_interfaces(index, data);
    printf("\n");

    index = parse_fields(index, data);
    printf("\n");

    index = parse_methods(index, data);
    printf("\n");

    index = parse_attributes(index, data);
    printf("\n");

    printf("parsed %d bytes of data for class file - success\n", index);
}