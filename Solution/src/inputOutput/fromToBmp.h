#ifndef UNTITLED_FROMTOBMP_H
#define UNTITLED_FROMTOBMP_H

#include "../image/image.h"
#include <stdbool.h>
#include <stdio.h>

struct __attribute__((packed)) bmp_header {
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t  biHeight;
    uint16_t  biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t  biClrImportant;
};

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


enum read_status fromBmp(FILE* in, struct image* image);
enum write_status toBmp(FILE* out, const struct image* image);
#endif //UNTITLED_FROMTOBMP_H
