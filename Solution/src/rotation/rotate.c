#include "../image/image.h"
#include <stdlib.h>

struct image rotate(const struct image source){
    if(source.data == NULL){
        return emptyImage(source.width, source.height, NULL);
    }

    struct pixel* pixels = malloc(sizeof(struct pixel) * source.width * source.height);

    for(size_t y = 0; y < source.height; y++){
        for(size_t x = 0; x < source.width; x++){
            pixels[findIndex(source.height - y - 1, x, source.height)] = source.data[findIndex(x, y, source.width)];
        }
    }

    return emptyImage(source.height, source.width, pixels);
}
