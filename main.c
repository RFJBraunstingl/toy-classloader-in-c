#include <stdio.h>

#include "./parse_class/parse_class.h"

#include "HelloWorld_class.h"
#include "Greeter_class.h"

int main() {
    printf("Hello, World!\n");

    parse_class(HelloWorld_class_data);
    // parse_class(Greeter_class_data);

    return 0;
}
