#include <stdio.h>

#include "./parse_class/parse_class.h"

#include "classes_combined.h"

int main() {
    printf("parsing class HelloWorld...\n");

    parse_class(all_class_files[0]);

    return 0;
}
