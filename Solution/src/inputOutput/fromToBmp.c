#include "fromToBmp.h"

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

enum read_status fromBmp(FILE* in, struct image* image){
    struct bmp_header header = {0};

    if(!head_read(in, &header)){
        imageDestroyer(image);
        return READ_INVALID_HEADER;
    }
    if(header.bfType != 19778){
        imageDestroyer(image);
        return READ_INVALID_SIGNATURE;
    }

    *image = createImage(header.biWidth, header.biHeight);
    const size_t padding = size_of_padding(image->width);

    for(size_t i = 0; i < image->height; i++){
        for(size_t j = 0; j < image->width; j++){
            if(!fread(&(image->data[findIndex(j, i, image->width)]), sizeof(struct pixel), 1, in)){
                imageDestroyer(image);
                return READ_INVALID_BITS;
            }
        }
        if(padding != 0) {
            if (fseek(in, padding, SEEK_CUR)) {
                imageDestroyer(image);
                return READ_INVALID_PADDING;
            }
        }
    }

    return READ_OK;
}

enum write_status toBmp(FILE* out, const struct image* image){
    struct bmp_header header = create_header(image);

    if(!fwrite(&header, sizeof(struct bmp_header), 1, out)){
        return WRITE_INVALID_HEADER;
    }

    if(fseek(out, header.bOffBits, SEEK_SET)){
        return WRITE_INVALID_SIGNATURE;
    }

    const uint8_t paddings[3] = {0};
    const size_t padding = size_of_padding(image->width);

    if(image->data == NULL){
        return WRITE_INVALID_DATA;
    }

    for(size_t i = 0; i < image->height; i++){
        for(size_t j = 0; j < image->width; j++) {
            if (!fwrite(&image->data[findIndex(j, i, image->width)], sizeof(struct pixel), 1, out)) {
                return WRITE_INVALID_BITS;
            }
        }
        if(padding != 0){
            if(!fwrite(paddings, padding, 1, out)){
                return WRITE_INVALID_PADDING;
            }
        }
    }
    return WRITE_OK;
}