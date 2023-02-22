#include <stdio.h>

#include "./bifit/bifit.h"

int main() {
    printf("parsing class HelloWorld...\n");

    // parse_class(bifit_embedded_class_files[0]);

    bifit_run();

    return 0;
}
