#include <stdio.h>

#include "./bifit/parse_class/parse_class.h"

#include "classes_combined.h"

int main() {
    printf("parsing class HelloWorld...\n");

    parse_class(bifit_embedded_class_files[0]);

    return 0;
}
