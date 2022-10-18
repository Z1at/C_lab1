#ifndef UNTITLED_FROMTOBMP_H
#define UNTITLED_FROMTOBMP_H

#include <stdio.h>
#include <stdbool.h>
#include "../image/image.h"

enum read_status  {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER,
    READ_INVALID_PADDING
};

enum write_status  {
    WRITE_OK = 0,
    WRITE_ERROR,
    WRITE_INVALID_BITS,
    WRITE_INVALID_SIGNATURE,
    WRITE_INVALID_HEADER,
    WRITE_INVALID_DATA,
    WRITE_INVALID_PADDING
};


enum read_status fromBmp(FILE* out, struct image* image);
enum write_status toBmp(FILE* out, const struct image* image);
#endif //UNTITLED_FROMTOBMP_H
