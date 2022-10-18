#include <stdint.h>
#include <stdlib.h>
#include "image.h"

size_t findIndex(const size_t x, const size_t y, const size_t width){
    return y * width + x;
}

struct image emptyImage(const uint64_t width, const uint64_t height, struct pixel* pixels){
    return (struct image) {.data = pixels, .width = width, .height = height};
}

struct image createImage(const size_t width, const size_t height){
    struct pixel* pixels = malloc(sizeof(struct pixel) * height * width);
    return emptyImage(width, height, pixels);
}

void imageDestroyer(struct image* image){
    free(image->data);
}


