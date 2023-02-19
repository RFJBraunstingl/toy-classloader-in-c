#include <stdio.h>

#include "./parse_class/combined.h"

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
    printf("\n");

    index = parse_fields(index, HelloWorld_class_data);
    printf("\n");

    index = parse_methods(index, HelloWorld_class_data);
    printf("\n");

    return 0;
}
