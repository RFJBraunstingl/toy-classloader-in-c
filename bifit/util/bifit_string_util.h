#ifndef BIFIT_STRING_UTIL_H_
#define BIFIT_STRING_UTIL_H_

#include <stdio.h>
#include "stdint.h"

void log_string_with_length(const uint8_t *arr, int len) {
    for (int i = 0; i < len; ++i) {
        LOG_DEBUG("%c", arr[i]);
    }
    LOG_DEBUG("\n");
}

#endif