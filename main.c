#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./parse_class/class_header.h"
#include "./parse_class/constant_pool.h"

#include "HelloWorld_class.h"
#include "Greeter_class.h"

int main() {
    printf("Hello, World!\n");

    // load class
    printf("loading class Hello World\n");
    parse_class_header(HelloWorld_class_data);
    int index = parse_constant_pool(HelloWorld_class_data);

    return 0;
}
