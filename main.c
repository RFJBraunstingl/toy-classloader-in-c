#include <stdio.h>

#include "./parse_class/class_header.h"
#include "./parse_class/constant_pool.h"
#include "./parse_class/parse_helpers.h"
#include "./parse_class/interfaces.h"

#include "HelloWorld_class.h"
#include "Greeter_class.h"

int main() {
    printf("Hello, World!\n");

    // load class
    printf("loading class Hello World\n");
    parse_class_header(HelloWorld_class_data);

    printf("\n");
    int index = parse_constant_pool(HelloWorld_class_data);

    printf("\n");
    index = parse_access_flags(index, HelloWorld_class_data);
    index = parse_this_class(index, HelloWorld_class_data);
    index = parse_super_class(index, HelloWorld_class_data);

    printf("\n");
    index = parse_interfaces(index, HelloWorld_class_data);

    return 0;
}
