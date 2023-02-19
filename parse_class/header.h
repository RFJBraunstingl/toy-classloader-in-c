#include <stdio.h>
#include <stdlib.h>

void guess_java_version(char *major_version, char *target);

/**
 * Read the first 8 bytes from the class file
 * which provide information about the java version
 *
 * @param data
 */
void parse_class_header(uint8_t data[]) {
    printf("magic number is '%x%x %x%x'\n",
           data[0],
           data[1],
           data[2],
           data[3]
    );

    printf("minor version: %x%x\n", data[4], data[5]);
    char major_version[4];
    sprintf(major_version, "%x%x", data[6], data[7]);
    printf("major version: %s\n", major_version);

    char java_version_description[10];
    guess_java_version(major_version, java_version_description);
    printf("guessing java version: %s\n", java_version_description);
}

void guess_java_version(char *major_version, char *target) {
    int version_number = (int) strtol(major_version, NULL, 16);
    printf("major version number is %d\n", version_number);

    int java_version = version_number - 44;

    sprintf(target, "Java %d", java_version);
}
