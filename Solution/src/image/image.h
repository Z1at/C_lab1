//
// Created by Zlat on 10/17/2022.
//

#ifndef UNTITLED_IMAGE_H
#define UNTITLED_IMAGE_H

#include <stdint.h>

struct __attribute__ ((packed)) pixel {
    uint8_t b;
    uint8_t g;
    uint8_t r;
};

struct image {
    uint64_t width;
    uint64_t height;
    struct pixel *data;
};

size_t findIndex(size_t x, size_t y, size_t width);
struct image emptyImage(const uint64_t width, const uint64_t height, struct pixel* pixels);
struct image createImage(const size_t image_width, const size_t image_height);
void imageDestroyer(struct image* image);


#endif //UNTITLED_IMAGE_H
