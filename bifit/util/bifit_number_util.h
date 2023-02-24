#ifndef BIFIT_NUMBER_UTIL_H_
#define BIFIT_NUMBER_UTIL_H_

int parse_integer_u2(unsigned int index, const uint8_t data[]) {
    int result = data[index];
    result  = result << 8;

    result += data[index + 1];

    return result;
}

int parse_integer_u4(unsigned int index, const uint8_t data[]) {
    int result = data[index++];
    result = result << 8;

    result += data[index++];
    result = result << 8;

    result += data[index++];
    result = result << 8;

    result += data[index];

    return result;
}

#endif