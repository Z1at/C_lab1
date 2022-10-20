#include "fromToBmp.h"
#include "../util/utilsForBmp.h"

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
