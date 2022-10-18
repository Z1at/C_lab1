#include "../inputOutput/fromToBmp.h"

size_t size_of_padding(const size_t width){
    return width % 4;
}

bool head_read(FILE* file, struct bmp_header* header){
    return fread(header, sizeof(struct bmp_header), 1, file);
}

size_t size_of_image(const struct image* image){
    return (image->width * sizeof(struct pixel) + size_of_padding(image->width)) * image->height;
}

size_t size_of_file(const struct image* image){
    return size_of_image(image) + sizeof(struct bmp_header);
}

struct bmp_header create_header(const struct image* image){
    return (struct bmp_header){
            .bfType = 19778,
            .bfileSize = size_of_file(image),
            .bfReserved = 0,
            .bOffBits = 54,
            .biSize = 40,
            .biWidth = image->width,
            .biHeight = image->height,
            .biPlanes = 1,
            .biBitCount = 24,
            .biCompression = 0,
            .biSizeImage = size_of_image(image),
            .biXPelsPerMeter = 0,
            .biYPelsPerMeter = 0,
            .biClrImportant = 0,
            .biClrUsed = 0
    };
}